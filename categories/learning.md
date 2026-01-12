---
layout: default
title: 学习笔记
---

<div class="category-page">
    <h1>📚 学习笔记</h1>
    <p>课程学习、知识整理、技能提升</p>
    
    <div class="posts-list">
        {% for post in site.categories.learning %}
        <article class="post-item">
            <h2><a href="{{ post.url | relative_url }}">{{ post.title }}</a></h2>
            <div class="post-meta">
                <time>{{ post.date | date: "%Y年%m月%d日" }}</time>
                {% if post.tags %}
                <span class="tags">
                    {% for tag in post.tags limit: 3 %}
                    <span class="tag">{{ tag }}</span>
                    {% endfor %}
                </span>
                {% endif %}
            </div>
            <p class="excerpt">{{ post.excerpt | strip_html | truncatewords: 30 }}</p>
        </article>
        {% endfor %}
    </div>
</div>
