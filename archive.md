---
layout: default
title: 归档
permalink: /archive/
---

<div class="archive-page">
    <h1>📚 文章归档</h1>
    <p>共 {{ site.posts | size }} 篇文章</p>
    
    {% assign postsByYear = site.posts | group_by_exp: "post", "post.date | date: '%Y'" %}
    
    {% for year in postsByYear %}
    <div class="archive-year">
        <h2>{{ year.name }} 年</h2>
        <ul class="archive-list">
            {% for post in year.items %}
            <li class="archive-item">
                <span class="date">{{ post.date | date: "%m-%d" }}</span>
                <a href="{{ post.url | relative_url }}">{{ post.title }}</a>
            </li>
            {% endfor %}
        </ul>
    </div>
    {% endfor %}
</div>

<style>
.archive-page h1 { margin-bottom: 0.5rem; }
.archive-page > p { color: #666; margin-bottom: 2rem; }
.archive-year { margin-bottom: 2rem; }
.archive-year h2 { 
    font-size: 1.5rem; 
    color: #2563eb; 
    border-bottom: 2px solid #e5e7eb; 
    padding-bottom: 0.5rem;
    margin-bottom: 1rem;
}
.archive-list { list-style: none; padding: 0; }
.archive-item { 
    display: flex; 
    align-items: baseline; 
    padding: 0.5rem 0;
    border-bottom: 1px solid #f3f4f6;
}
.archive-item .date { 
    font-family: monospace; 
    color: #9ca3af; 
    min-width: 60px;
    margin-right: 1rem;
}
.archive-item a { 
    color: #374151; 
    text-decoration: none;
}
.archive-item a:hover { 
    color: #2563eb; 
}
</style>
