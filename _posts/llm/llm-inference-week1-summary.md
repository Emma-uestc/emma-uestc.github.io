---
layout: post
title: "环境搭建和基础部署"
date: 2025-07-24 16:00:00 +0800
categories: [work]
tags: [大模型部署, 开始, vllm]
---  
# 大模型推理部署实战（一）：vLLM从入门到生产  

> 记录从零开始学习大模型推理部署的完整过程，基于vGPU云服务器环境  
## 🎯 本周成果

- ✅ 成功部署Qwen2-7B模型，实现156 tokens/s的优秀性能
- ✅ 搭建OpenAI兼容API服务，支持25个标准端点
- ✅ 建立完整的服务管理体系，包含启动、监控、测试
- ✅ 掌握vGPU环境特点和优化策略

## 🏗️ 环境配置

### 硬件环境
- **云平台**: InternStudio开发机，这里感谢上海人工智能实验室的算力支持(参加了训练营获得的算力)
- **GPU**: A100-80GB的30%算力 (约24GB显存)
- **优势**: 成本低、配置灵活、开箱即用

### 软件安装
```bash
# 创建环境
conda create -n llm-inference python=3.10
conda activate llm-inference

# 安装依赖
pip install torch==2.4.0+cu121 torchvision torchaudio --extra-index-url https://download.pytorch.org/whl/cu121
# 安装vLLM
pip install vllm
# 验证安装
python -c "import vllm; print('vLLM安装成功')"
```   
### 配置模型下载镜像
```bash
# 设置Hugging Face镜像（可选，提升下载速度）
export HF_ENDPOINT=https://hf-mirror.com
```

## 什么是vLLM？
vLLM是Berkeley开发的高性能大语言模型推理框架，主要优势：
- **PagedAttention**：革命性的注意力机制优化，类似操作系统的虚拟内存
- **Continuous Batching**：动态批处理，自动优化吞吐量
- **CUDA Graph**：GPU计算图优化，减少启动开销   

## 🚀 核心实现

### 1. 基础模型部署

```python
# deploy_basic.py
from vllm import LLM, SamplingParams

def deploy_basic_model():
    # 模型配置
    llm = LLM(
        model="Qwen/Qwen2-7B-Instruct",
        tensor_parallel_size=1,
        gpu_memory_utilization=0.8,
        max_model_len=4096,
        trust_remote_code=True
    )
    
    # 采样参数
    sampling_params = SamplingParams(
        temperature=0.7,
        top_p=0.9,
        max_tokens=512
    )
    
    # 推理测试
    prompts = ["解释一下什么是深度学习", "用Python写一个快速排序算法"]
    outputs = llm.generate(prompts, sampling_params)
    
    for output in outputs:
        print(f"输入: {output.prompt}")
        print(f"输出: {output.outputs[0].text}")
```

**关键代码:**   
* 导入模块部分    
- `LLM`：vLLM的核心类，负责模型加载和推理
- `SamplingParams`：控制文本生成的参数类，影响输出质量和随机性  

* 模型配置部分  
```python
model_name = "Qwen/Qwen2-7B-Instruct"
llm = LLM(
    model=model_name,
    tensor_parallel_size=1,
    gpu_memory_utilization=0.8,
    max_model_len=4096,
    trust_remote_code=True
)
```  
- `Qwen2-7B-Instruct`：阿里的70亿参数指令微调模型，适合对话任务
- `tensor_parallel_size=1`：使用1个GPU，如果有多GPU可以增加此值进行并行
- `gpu_memory_utilization=0.8`：使用80%的GPU显存，留20%作为缓冲避免OOM
- `max_model_len=4096`：最大支持4096个token的上下文长度
- `trust_remote_code=True`：允许执行模型仓库中的自定义代码  

### 执行日志详细分析  
**性能表现:**
- 模型加载: 14.25GB显存，58.55s
- 推理速度: 156 tokens/s (超出30% vGPU理论值)
- 并发能力: 15.57x (4K context)   

下面是按阶段分析  
#### 模型加载阶段  
```
INFO 07-23 10:22:08 [config.py:841] This model supports multiple tasks: {'classify', 'generate', 'reward', 'embed'}
```
**解析：** Qwen2模型是多任务模型，支持分类、生成、奖励建模和嵌入等任务，这里默认使用生成任务。

```
INFO 07-23 10:22:09 [config.py:1472] Using max model len 4096
INFO 07-23 10:22:09 [config.py:2285] Chunked prefill is enabled with max_num_batched_tokens=8192
```
**解析：** 
- 确认最大序列长度为4096
- 启用了分块预填充优化，批处理token数为8192，这能提高长序列的处理效率  

#### GPU和内存配置
```
INFO 07-23 10:22:14 [parallel_state.py:1076] rank 0 in world size 1 is assigned as DP rank 0, PP rank 0, TP rank 0, EP rank 0
```
**解析：** 这是分布式配置信息：
- DP (Data Parallel): 数据并行rank 0
- PP (Pipeline Parallel): 流水线并行rank 0  
- TP (Tensor Parallel): 张量并行rank 0
- EP (Expert Parallel): 专家并行rank 0
- 都是0表示单GPU运行

#### 模型权重加载   
```
Loading safetensors checkpoint shards: 100% Completed | 4/4 [00:03<00:00, 1.32it/s]
INFO 07-23 10:22:20 [default_loader.py:272] Loading weights took 3.22 seconds
INFO 07-23 10:22:20 [gpu_model_runner.py:1801] Model loading took 14.2488 GiB and 5.173644 seconds
```
**关键信息：**
- 模型分为4个分片文件（safetensors格式，比pickle更安全）
- 权重加载耗时3.22秒
- **模型占用显存14.25GB**，这是7B模型的典型显存占用  

#### 编译优化阶段   
```
INFO 07-23 10:22:36 [backends.py:508] Using cache directory: /root/.cache/vllm/torch_compile_cache/
INFO 07-23 10:22:36 [backends.py:519] Dynamo bytecode transform time: 15.38 s
INFO 07-23 10:22:49 [backends.py:155] Directly load the compiled graph(s) for shape None from the cache, took 12.922 s
```
**解析：** 
- vLLM使用了PyTorch的`torch.compile`进行模型编译优化
- 首次运行需要编译时间，后续运行会使用缓存
- 编译能带来10-20%的推理加速  

#### KV Cache配置  
```
INFO 07-23 10:22:56 [gpu_worker.py:232] Available KV cache memory: 3.41 GiB
INFO 07-23 10:22:57 [kv_cache_utils.py:716] GPU KV cache size: 63,776 tokens
INFO 07-23 10:22:57 [kv_cache_utils.py:720] Maximum concurrency for 4,096 tokens per request: 15.57x
```
**重要概念 - KV Cache：**
- **KV Cache**是注意力机制的核心优化，缓存Key和Value矩阵避免重复计算
- 可用KV Cache内存：3.41GB（剩余显存的一部分）
- 可缓存63,776个token
- **并发度15.57x**：理论上可以同时处理15个4096长度的请求   

### CUDA Graph优化
```
Capturing CUDA graph shapes: 100%|█████████████████| 67/67 [00:21<00:00, 3.05it/s]
INFO 07-23 10:23:19 [gpu_model_runner.py:2326] Graph capturing finished in 22 secs, took 1.56 GiB
```
**解析：**
- **CUDA Graph**：预先录制GPU操作序列，减少CPU-GPU通信开销
- 捕获了67种不同的形状配置
- 额外占用1.56GB显存，但能显著提升推理速度

### 推理性能分析
```
Processed prompts: 100%|███████████████| 2/2 [00:05<00:00, 2.54s/it, est. speed input: 2.36 toks/s, output: 156.19 toks/s]
```
**性能指标解析：**
- **输入处理速度**：2.36 tokens/s（相对较慢，因为需要处理prompt）
- **输出生成速度**：156.19 tokens/s（这是关键指标）
- **总耗时**：2个prompt共5秒，平均每个2.5秒

### 2. API服务化

```bash
# 启动OpenAI兼容API服务
python -m vllm.entrypoints.openai.api_server \
    --model Qwen/Qwen2-7B-Instruct \
    --served-model-name qwen2-7b \
    --host 0.0.0.0 \
    --port 8000 \
    --gpu-memory-utilization 0.8 \
    --max-model-len 4096
```
**API测试脚本:**
```python
# test_api.py
import requests
import json

def test_openai_api():
    url = "http://localhost:8000/v1/chat/completions"
    data = {
        "model": "qwen2-7b",
        "messages": [{"role": "user", "content": "你好，请介绍一下自己"}],
        "temperature": 0.7,
        "max_tokens": 512
    }
    
    response = requests.post(url, 
        headers={"Content-Type": "application/json"}, 
        json=data)
    
    if response.status_code == 200:
        result = response.json()
        print(json.dumps(result, indent=2, ensure_ascii=False))
```

### 3. 生产级服务管理   
上面使用命令行启动，实际生产环境我们都是后台运行，并且需要对服务进行监控的。  
我这里提供了一个简单脚本用于管理服务，完整脚本会上传到我的仓库。  

**服务管理脚本:**
```bash
#!/bin/bash
# manage_api_service.sh

start_service() {
    screen -dmS vllm-api bash -c "
        conda activate llm-inference
        python -m vllm.entrypoints.openai.api_server \
            --model Qwen/Qwen2-7B-Instruct \
            --served-model-name qwen2-7b \
            --host 0.0.0.0 --port 8000 \
            --gpu-memory-utilization 0.8 \
            --max-model-len 4096
    "
}

# 使用方式
./manage_api_service.sh start   # 启动
./manage_api_service.sh status  # 状态
./manage_api_service.sh test    # 测试
./manage_api_service.sh stop    # 停止
```  
一开始是打算使用screen 的，环境所限，最后还是使用了nohup。  
```bash
#!/bin/bash
# simple_service_manager.sh
# 简单的vLLM API服务管理脚本 (无外部依赖)
start_service() {
    echo "启动vLLM API服务..."
    ....

    nohup python -m vllm.entrypoints.openai.api_server \
        --model Qwen/Qwen2-7B-Instruct \
        --served-model-name qwen2-7b \
        --host 0.0.0.0 \
        --port $SERVICE_PORT \
        --gpu-memory-utilization 0.8 \
        --max-model-len 4096 > $LOG_FILE 2>&1 &
```  
使用方式同上。   

## 📊 技术深度分析

### vLLM核心技术

**1. PagedAttention机制**
- 类似OS虚拟内存管理
- 动态分配KV-Cache块
- 显存利用率提升2-4x

**2. Continuous Batching**
- 动态批处理优化
- 自动调整吞吐量
- 减少GPU空闲时间

**3. CUDA Graph优化**
- 预录制GPU操作序列
- 减少CPU-GPU通信
- 性能提升10-20%

### vGPU环境特点

**架构分析:**
```
物理A100-80GB (100%)
├── 用户1: 30%算力 + 24GB显存 (我的环境)
├── 用户2: 40%算力 + 32GB显存
└── 用户3: 30%算力 + 24GB显存
```

**性能对比:**
| 指标 | 物理A100 | 30% vGPU | 实际表现 |
|------|----------|----------|----------|
| 理论性能 | 500 tokens/s | 150 tokens/s | 156 tokens/s ✅ |
| 显存容量 | 80GB | 24GB | 24GB |
| 并发能力 | 完整 | 受限 | 15.57x |

## 🎯 下周计划

### 第二周学习目标
- [ ] **模型量化**: AWQ、GPTQ等技术实践
- [ ] **批处理优化**: 动态batching性能调优
- [ ] **并发测试**: 高负载场景下的性能表现
- [ ] **监控体系**: 详细的性能监控和告警

### 扩展方向
- 🐳 **容器化**: Docker部署和编排
- 📊 **监控**: Prometheus + Grafana
- 🔗 **多模型**: 模型路由和管理
- 🛡️ **安全**: 认证授权机制

## 📚 学习资源

- [vLLM官方文档](https://docs.vllm.ai/)
- [Qwen2模型](https://github.com/QwenLM/Qwen2)
- [OpenAI API参考](https://platform.openai.com/docs/api-reference)