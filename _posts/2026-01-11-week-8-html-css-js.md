---
layout: post
title: "CS50 Week 8: HTML, CSS, JavaScript"
date: 2026-01-11 10:00:00 +0800
categories: [learning]
tags: [HTML, CSS, JavaScript, Web开发, 前端]
---

之前课程，我们学习了高级编程语言 Python，它与 C 语言类似，也是通过把功能放到特定模块中构建。今天，我们将进一步扩展这些构建模块，深入探索HTML、CSS和JavaScript。
# 互联网    
互联网将全球计算机相互连接，是一项我们都在使用的技术。
运用前几周掌握的技能，我们可以构建自己的网页和应用程序。
ARPANET首次将互联网上的节点相互连接起来。
两点之间的节点可视为路由器。
# 路由器  
要将数据从一处路由到另一处，我们需要做出路由决策。也就是说，需要有人编程设定数据从点A传输到点B的途径。
可以想象数据从点A到点B可能存在多条路径，这样当某台路由器拥塞时，数据就能通过其他路径流动。数据包就这样从一台路由器传递到另一台，从一台计算机传递到另一台。
TCP/IP是两项协议，使计算机能够通过互联网相互传输数据。
IP（互联网协议）是计算机在互联网上相互识别的途径。每台计算机在全球范围内都有唯一的地址，其格式如下：
`#.#.#.#`  
数字范围为0至255。IP地址采用32位（IPv4），意味着可支持超过40亿个地址。新型IP地址（如IPv6）采用128位设计，能支持数量庞大的计算机！
现实世界中，服务器承担着大量工作。
数据包结构如下： 
```
0                   1                   2                   3  
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version|  IHL  |Type of Service|          Total Length         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Identification        |Flags|      Fragment Offset    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Time to Live |    Protocol   |         Header Checksum       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Source Address                          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Destination Address                        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Options                    |    Padding    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```  
数据包是标准化的。每个数据包内都包含源地址和目标地址。
传输控制协议（TCP）有助于追踪发送数据包的顺序。
此外，TCP用于区分不同的网络服务。例如，80端口用于表示HTTP，443端口用于表示HTTPS。这些数字是这些服务的默认端口号。
信息在不同位置间传输时，会发送源IP地址、目标IP地址及TCP端口号。
这些协议还用于将大型文件分割为多个片段或数据包。例如，一张大型猫咪照片可拆分为多个数据包发送。当数据包丢失时，TCP/IP可向源服务器重新请求缺失数据包。
当所有数据完成传输与接收后，TCP将发送确认信息。 
# DNS  
若需记住IP地址才能访问网站，那将非常繁琐。
DNS（域名系统）是由互联网上的服务器组成的集合，用于将网站地址（如harvard.edu）路由到特定IP地址。
DNS本质上是一个表格或数据库，用于将特定的完全合格域名与特定IP地址建立关联。  
# DHCP  
DHCP是一种为设备分配IP地址的协议。
此外，该协议还定义了设备使用的默认网关和域名服务器。
现在，暂且搁置比喻信封之外的内容：让我们打开信封一探究竟。 
# HTTPS  
HTTP（超文本传输协议）是一种应用层协议，开发人员通过它在不同位置之间传输数据来构建强大且实用的系统。HTTPS则是该协议的安全版本。  
当你看到一个地址，比如 https://www.example.com 时，你实际上是在以 / 结尾的情况下隐式地访问该地址。  
路径就是斜杠之后的部分。例如，访问 https://www.example.com/folder/file.html 时，系统会先访问 example.com，然后浏览到名为 directory 的文件夹，最后访问名为 file.html 的文件。
`.com` 被称为顶级域名，用于表示与此地址相关联的位置或组织类型。  
`https` 在这个地址中是指用于连接该网址的协议。我们所说的协议是指 `HTTP` 使用 `GET` 或 `POST` 请求来向服务器索取信息。例如，你可以打开 `Google Chrome`，右键点击，然后点击 `inspect` 。当你打开 `developer tools` 并访问 `Network` ，选择 `Preserve log` 时，你会看到 R`equest Headers` 。你会看到提及 `GET` 的内容。在其他浏览器中，也可以通过略微不同的方法实现这一点。  
例如，当发起一个 GET 请求时，你的计算机可能会向服务器发送以下内容：  
```
GET / HTTP/2
Host: www.harvard.edu
```  
这个请求通过 HTTP2 获取在 `www.harvard.edu` 上提供的内容。  
通常，在向服务器发起请求后，你会在 `Response Headers` 中收到以下内容：  
```
HTTP/2 200
Content-Type: text/html
```  
这种检查这些日志的方法可能比必要的更复杂一些。你可以在 [cs50.dev](https://cs50.dev/) 上分析 HTTP 协议的工作。例如，在终端窗口中输入以下内容：  
`curl -I https://www.harvard.edu/`  
请注意，这个命令的返回了服务端响应的所有 `header` 。  
通过浏览器的开发者工具，可以在访问上述网站时查看所有HTTP请求。
此外，在终端窗口中执行命令：`curl -I https://harvard.edu`  
注意，返回一个状态码 301 响应，该响应会向浏览器提示正确网站的访问地址。
同样地，在终端窗口中执行操作：`curl -I http://www.harvard.edu/`   
请注意`https`中的`s`已被移除。服务端响应将显示状态码为301，这意味着该网站已永久迁移。 
与`301`类似，`404`状态码表示指定的URL未找到。还有许多其他响应代码，例如： 
```
200 OK
301 Moved Permanently
302 Found
304 Not Modified
307 Temporary Redirect
401 Unauthorized
403 Forbidden
404 Not Found
418 I'm a Teapot
500 Internal Server Error
503 Service Unavailable
```  
值得一提的是，当`500`错误涉及你开发的产品或应用时，通常是开发者自身的责任。这一点对下周的习题集至关重要，甚至可能影响你的最终项目！不过，`500`错误也可能源于基础设施问题或第三方服务故障。 
# HTML  
HTML（超文本标记语言）由标签构成，每个标签可能带有描述其属性的属性。
在终端中输入 `code hello.html`，并按以下方式编写代码：  
```html
<!DOCTYPE html>

<!-- Demonstrates HTML -->

<html lang="en">
    <head>
        <title>hello, title</title>
    </head>
    <body>
        hello, body
    </body>
</html>
```  
请注意，`html`标签既开启又结束了此文件。此外，请注意`lang`属性，它会改变`html`标签的行为。同时请注意，文件中既包含`head`标签也包含`body`标签。缩进虽非必需，但能体现层级关系。  
你可以通过输入 `http-server` 来运行代码。现在，通过这个非常长的 `URL` 即可访问你代码生成的内容。点击该链接，即可访问由你自己的代码生成的网站。
访问该 `URL` 时，请注意 `URL` 末尾出现了文件名 `hello.html`。此外，根据 `URL` 可知，服务器是通过端口 8080 进行服务的。
```bash
http-server
Starting up http-server, serving ./

http-server settings: 
CORS: true
Cache: -1 seconds
Connection Timeout: 120 seconds
Directory Listings: visible
AutoIndex: not visible
Serve GZIP Files: false
Serve Brotli Files: false
Default File Extension: none

Available on:
  https://psychic-giggle-97g4ww5rxjq27rjx-8080.app.github.dev
Hit CTRL-C to stop the server

[2026-01-07T03:01:16.780Z]  "GET /" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/143.0.0.0 Safari/537.36"
[2026-01-07T03:01:20.787Z]  "GET /favicon.ico" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/143.0.0.0 Safari/537.36"
[2026-01-07T03:01:20.789Z]  "GET /favicon.ico" Error (404): "Not found"
```   
![](/assets/images/cs50/hello-html.png)
标签的层级结构可表示如下：
[](https://cs50.harvard.edu/x/notes/8/cs50Week8Slide065.png)  
了解这种层级结构对后续学习JavaScript会很有帮助。
浏览器会从上到下、从左到右读取HTML文件。
由于HTML中空格和缩进基本会被忽略，因此需要使用`<p>`段落标签来开启和结束段落。请看以下示例： 
```html
<!DOCTYPE html>

<!-- Demonstrates paragraphs -->

<html lang="en">
    <head>
        <title>paragraphs</title>
    </head>
    <body>
        <p>
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus convallis scelerisque quam, vel hendrerit lectus viverra eu. Praesent posuere eget lectus ut faucibus. Etiam eu velit laoreet, gravida lorem in, viverra est. Cras ut purus neque. In porttitor non lorem id lobortis. Mauris gravida metus libero, quis maximus dui porta at. Donec lacinia felis consectetur venenatis scelerisque. Nulla eu nisl sollicitudin, varius velit sit amet, vehicula erat. Curabitur sollicitudin felis sit amet orci mattis, a tempus nulla pulvinar. Aliquam erat volutpat.
        </p>
        <p>
            Mauris ut dui in eros semper hendrerit. Morbi vel elit mi. Sed sit amet ex non quam dignissim dignissim et vel arcu. Pellentesque eget elementum orci. Morbi ac cursus ex. Pellentesque quis turpis blandit orci dapibus semper sed non nunc. Nulla et dolor nec lacus finibus volutpat. Sed non lorem diam. Donec feugiat interdum interdum. Vivamus et justo in enim blandit fermentum vel at elit. Phasellus eu ante vitae ligula varius aliquet. Etiam id posuere nibh.
        </p>
        <p>
            Aenean venenatis convallis ante a rhoncus. Nullam in metus vel diam vehicula tincidunt. Donec lacinia metus sem, sit amet egestas elit blandit sit amet. Nunc egestas sem quis nisl mattis semper. Pellentesque ut magna congue lorem eleifend sodales. Donec tortor tortor, aliquam vitae mollis sed, interdum ut lectus. Mauris non purus quis ipsum lacinia tincidunt.
        </p>
        <p>
            Integer at justo lacinia libero blandit aliquam ut ut dui. Quisque tincidunt facilisis venenatis. Nullam dictum odio quis lorem luctus, vel malesuada dolor luctus. Aenean placerat faucibus enim a facilisis. Maecenas eleifend quis massa sed eleifend. Ut ultricies, dui ac vulputate hendrerit, ex metus iaculis diam, vitae fermentum libero dui et ante. Phasellus suscipit, arcu ut consequat sagittis, massa urna accumsan massa, eu aliquet nulla lorem vitae arcu. Pellentesque rutrum felis et metus porta semper. Nam ac consectetur mauris.
        </p>
        <p>
            Suspendisse rutrum vestibulum odio, sed venenatis purus condimentum sed. Morbi ornare tincidunt augue eu auctor. Vivamus sagittis ac lectus at aliquet. Nulla urna mauris, interdum non nibh in, vehicula porta enim. Donec et posuere sapien. Pellentesque ultrices scelerisque ipsum, vel fermentum nibh tincidunt et. Proin gravida porta ipsum nec scelerisque. Vestibulum fringilla erat at turpis laoreet, nec hendrerit nisi scelerisque.
        </p>
        <p>
            Sed quis malesuada mi. Nam id purus quis augue sagittis pharetra. Nulla facilisi. Maecenas vel fringilla ante. Cras tristique, arcu sit amet blandit auctor, urna elit ultricies lacus, a malesuada eros dui id massa. Aliquam sem odio, pretium vel cursus eget, scelerisque at urna. Vestibulum posuere a turpis consectetur consectetur. Cras consequat, risus quis tempor egestas, nulla ipsum ornare erat, nec accumsan nibh lorem nec risus. Integer at iaculis lacus. Integer congue nunc massa, quis molestie felis pellentesque vestibulum. Nulla odio tortor, aliquam nec quam in, ornare aliquet sapien.
        </p>
    </body>
</html>
```  
注意
HTML还允许表示 head： 
```html
<!DOCTYPE html>

<!-- Demonstrates headings (for chapters, sections, subsections, etc.) -->

<html lang="en">

    <head>
        <title>headings</title>
    </head>

    <body>

        <h1>One</h1>
        <p>
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus convallis scelerisque quam, vel hendrerit lectus viverra eu. Praesent posuere eget lectus ut faucibus. Etiam eu velit laoreet, gravida lorem in, viverra est. Cras ut purus neque. In porttitor non lorem id lobortis. Mauris gravida metus libero, quis maximus dui porta at. Donec lacinia felis consectetur venenatis scelerisque. Nulla eu nisl sollicitudin, varius velit sit amet, vehicula erat. Curabitur sollicitudin felis sit amet orci mattis, a tempus nulla pulvinar. Aliquam erat volutpat.
        </p>

        <h2>Two</h2>
        <p>
            Mauris ut dui in eros semper hendrerit. Morbi vel elit mi. Sed sit amet ex non quam dignissim dignissim et vel arcu. Pellentesque eget elementum orci. Morbi ac cursus ex. Pellentesque quis turpis blandit orci dapibus semper sed non nunc. Nulla et dolor nec lacus finibus volutpat. Sed non lorem diam. Donec feugiat interdum interdum. Vivamus et justo in enim blandit fermentum vel at elit. Phasellus eu ante vitae ligula varius aliquet. Etiam id posuere nibh.
        </p>

        <h3>Three</h3>
        <p>
            Aenean venenatis convallis ante a rhoncus. Nullam in metus vel diam vehicula tincidunt. Donec lacinia metus sem, sit amet egestas elit blandit sit amet. Nunc egestas sem quis nisl mattis semper. Pellentesque ut magna congue lorem eleifend sodales. Donec tortor tortor, aliquam vitae mollis sed, interdum ut lectus. Mauris non purus quis ipsum lacinia tincidunt.
        </p>

        <h4>Four</h4>
        <p>
            Integer at justo lacinia libero blandit aliquam ut ut dui. Quisque tincidunt facilisis venenatis. Nullam dictum odio quis lorem luctus, vel malesuada dolor luctus. Aenean placerat faucibus enim a facilisis. Maecenas eleifend quis massa sed eleifend. Ut ultricies, dui ac vulputate hendrerit, ex metus iaculis diam, vitae fermentum libero dui et ante. Phasellus suscipit, arcu ut consequat sagittis, massa urna accumsan massa, eu aliquet nulla lorem vitae arcu. Pellentesque rutrum felis et metus porta semper. Nam ac consectetur mauris.
        </p>

        <h5>Five</h5>
        <p>
            Suspendisse rutrum vestibulum odio, sed venenatis purus condimentum sed. Morbi ornare tincidunt augue eu auctor. Vivamus sagittis ac lectus at aliquet. Nulla urna mauris, interdum non nibh in, vehicula porta enim. Donec et posuere sapien. Pellentesque ultrices scelerisque ipsum, vel fermentum nibh tincidunt et. Proin gravida porta ipsum nec scelerisque. Vestibulum fringilla erat at turpis laoreet, nec hendrerit nisi scelerisque.
        </p>

        <h6>Six</h6>
        <p>
            Sed quis malesuada mi. Nam id purus quis augue sagittis pharetra. Nulla facilisi. Maecenas vel fringilla ante. Cras tristique, arcu sit amet blandit auctor, urna elit ultricies lacus, a malesuada eros dui id massa. Aliquam sem odio, pretium vel cursus eget, scelerisque at urna. Vestibulum posuere a turpis consectetur consectetur. Cras consequat, risus quis tempor egestas, nulla ipsum ornare erat, nec accumsan nibh lorem nec risus. Integer at iaculis lacus. Integer congue nunc massa, quis molestie felis pellentesque vestibulum. Nulla odio tortor, aliquam nec quam in, ornare aliquet sapien.
        </p>

    </body>

</html>
```  
 <h1>、<h2> 和 <h3> 表示不同级别的 head。  
 我们还可以在HTML中创建无序列表：  
 ```html
 <!DOCTYPE html>

<!-- Demonstrates (unordered) lists -->

<html lang="en">
    <head>
        <title>list</title>
    </head>
    <body>
        <ul>
            <li>foo</li>
            <li>bar</li>
            <li>baz</li>
        </ul>
    </body>
</html>
```  
<ul> 标签创建了一个包含三个 item 的无序列表。  
也可以在 HTML 中创建有序列表：  
```html
<!DOCTYPE html>

<!-- Demonstrates (ordered) lists -->

<html lang="en">
    <head>
        <title>list</title>
    </head>
    <body>
        <ol>
            <li>foo</li>
            <li>bar</li>
            <li>baz</li>
        </ol>
    </body>
</html>
```  
<ol> 标签创建了一个包含三个 item 的有序列表。
可以在 HTML 中创建一个表格：  
```html
<!DOCTYPE html>

<!-- Demonstrates table -->

<html lang="en">
    <head>
        <title>table</title>
    </head>
    <body>
        <table>
            <tr>
                <td>1</td>
                <td>2</td>
                <td>3</td>
            </tr>
            <tr>
                <td>4</td>
                <td>5</td>
                <td>6</td>
            </tr>
            <tr>
                <td>7</td>
                <td>8</td>
                <td>9</td>
            </tr>
            <tr>
                <td>*</td>
                <td>0</td>
                <td>#</td>
            </tr>
        </table>
    </body>
</html>
```  
HTML 中还可以添加图片：  
```
<!DOCTYPE html>

<!-- Demonstrates image -->

<html lang="en">
    <head>
        <title>image</title>
    </head>
    <body>
        <img alt="photo of bridge" src="bridge.png">
    </body>
</html>
```  
HTML 中嵌入视频   
```html
<!DOCTYPE html>

<!-- Demonstrates video -->

<html lang="en">
    <head>
        <title>video</title>
    </head>
    <body>
        <video controls muted>
            <source src="video.mp4" type="video/mp4">
        </video>
    </body>
</html>
```    

`type` 属性表明这是一个类型为 `mp4` 的视频。此外，注意 `controls` 和 `muted` 是如何传递给 video 的。  
还可以在不同的网页之间建立链接，即嵌入其它页面。  
```html
<!DOCTYPE html>

<!-- Demonstrates link -->

<html lang="en">
    <head>
        <title>link</title>
    </head>
    <body>
      Visit <a href="image.html">Harvard</a>.
    </body>
</html>
```  
使用 `<a>` 或`>`标签将 Harvard 转换为可链接的文本。 
也可以创建类似 Google 搜索的表单：  
```html
<!DOCTYPE html>

<!-- Demonstrates form -->

<html lang="en">
    <head>
        <title>search</title>
    </head>
    <body>
        <form action="https://www.google.com/search" method="get">
            <input name="q" type="search">
            <input type="submit" value="Google Search">
        </form>
    </body>
</html>
```  
一个 `form` 标签会打开并提供它将接受的` action` 属性的说明。 `input` 字段包含在内，传递名称 `q` 和类型作为 `search` 。  
可以通过以下方式改进这个搜索：
```html
<!DOCTYPE html>

<!-- Demonstrates additional form attributes -->

<html lang="en">
    <head>
        <title>search</title>
    </head>
    <body>
        <form action="https://www.google.com/search" method="get">
            <input autocomplete="off" autofocus name="q" placeholder="Query" type="search">
            <button>Google Search</button>
        </form>
    </body>
</html>
```  
# 正则表达式   
正则表达式是一种确保用户提供的数据符合特定格式的手段。  
可以实现一个使用正则表达式的自定义注册页面，如下所示：  
```html
<!DOCTYPE html>

<!-- Demonstrates type="email" -->

<html lang="en">
    <head>
        <title>register</title>
    </head>
    <body>
        <form>
            <input autocomplete="off" autofocus name="email" placeholder="Email" type="email">
            <button>Register</button>
        </form>
    </body>
</html>
```  
i`nput` 标签包含指定其类型为 `email` 的属性。浏览器会再次检查输入是否为电子邮件地址。  
虽然浏览器使用这些内置属性来检查电子邮件地址，但我们可以添加一个 `pattern` 属性，以确保只有特定数据出现在电子邮件地址中：  
```html
<!DOCTYPE html>

<!-- Demonstrates pattern attribute for email -->

<html lang="en">
    <head>
        <title>register</title>
    </head>
    <body>
        <form>
            <input autocomplete="off" autofocus name="email" pattern=".+@.+\.edu" placeholder="Email" type="email">
            <button>Register</button>
        </form>
    </body>
</html>
```  
注意， `pattern` 属性被赋予了一个正则表达式，以表示电子邮件地址必须包含一个 `@` 符号和一个 `.edu` 。  
# CSS  
