"""
aide SDK - AI手机助手 Python SDK
"""

from setuptools import setup, find_packages

with open("README.md", "w", encoding="utf-8") as f:
    f.write("# aide SDK\n\n")
    f.write("AI手机助手 Python SDK\n\n")
    f.write("## 安装\n\n")
    f.write("```bash\n")
    f.write("pip install aide-sdk\n")
    f.write("```\n\n")
    f.write("## 快速开始\n\n")
    f.write("```python\n")
    f.write("from aide_sdk import AideClient\n\n")
    f.write("client = AideClient(base_url=\"http://localhost:8080\")\n")
    f.write("result = client.chat(\"你好\")\n")
    f.write("print(result)\n")
    f.write("```\n")

with open("README.md", "a", encoding="utf-8") as f:
    f.write("## API\n\n")
    f.write("### 对话\n")
    f.write("```python\n")
    f.write("client.chat(\"你好\")\n")
    f.write("```\n\n")
    f.write("### 语音合成\n")
    f.write("```python\n")
    f.write("client.tts(\"你好\")\n")
    f.write("```\n\n")
    f.write("### 技能调用\n")
    f.write("```python\n")
    f.write("client.skills.weather(\"北京\")\n")
    f.write("client.skills.play_music(song=\"演员\")\n")
    f.write("```\n")

setup(
    name="aide-phone-sdk",
    version="0.1.0",
    description="AIDE AI Phone Assistant Python SDK",
    long_description=open("README.md", encoding="utf-8").read(),
    long_description_content_type="text/markdown",
    author="aide Team",
    author_email="dev@aide.dev",
    url="https://github.com/gaojinha/aide",
    packages=find_packages(),
    install_requires=[
        "requests>=2.28.0",
    ],
    extras_require={
        "stream": ["sseclient-py>=0.0.1"],
    },
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
    ],
    python_requires=">=3.8",
)
