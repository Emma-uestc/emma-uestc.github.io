---
layout: default
title: 生活随笔
---

<div class="category-page">
    <h1>🌸 生活随笔</h1>
    <p>日常感悟、旅行记录、兴趣爱好</p>
    
    <div class="posts-list">
        {% for post in site.categories.life %}
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
