"""
aide SDK CLI
"""

import sys
import argparse
from . import AideClient

def main():
    parser = argparse.ArgumentParser(description="aide SDK CLI")
    parser.add_argument("--url", default="http://localhost:8080", help="API 服务器地址")
    parser.add_argument("--key", default=None, help="API 密钥")
    
    subparsers = parser.add_subparsers(dest="command")
    
    # status
    subparsers.add_parser("status", help="查看状态")
    
    # chat
    chat_parser = subparsers.add_parser("chat", help="对话")
    chat_parser.add_argument("message", help="消息内容")
    
    # tts
    tts_parser = subparsers.add_parser("tts", help="语音合成")
    tts_parser.add_argument("text", help="文本内容")
    
    # skills
    subparsers.add_parser("skills", help="列出技能")
    
    # settings
    subparsers.add_parser("settings", help="获取设置")
    
    args = parser.parse_args()
    
    client = AideClient(base_url=args.url, api_key=args.key)
    
    if args.command == "status":
        print(client.get_status())
    elif args.command == "chat":
        print(client.chat(args.message))
    elif args.command == "tts":
        print(client.tts(args.text))
    elif args.command == "skills":
        print(client.list_skills())
    elif args.command == "settings":
        print(client.get_settings())
    else:
        parser.print_help()
    
    client.close()

if __name__ == "__main__":
    main()
