import http.server
import socketserver
import webbrowser
import threading
import os

PORT = 8000

class Handler(http.server.SimpleHTTPRequestHandler):
    def translate_path(self, path):
        if path == '/':
            return os.path.join(os.getcwd(), 'web', 'index.html')
        elif path == '/network.json':
            return os.path.join(os.getcwd(), 'web', 'network.json')
        else:
            return os.path.join(os.getcwd(), 'web', path.lstrip('/'))

def start_server():
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print(f"Szerver fut: http://localhost:{PORT}")
        webbrowser.open(f"http://localhost:{PORT}")
        httpd.serve_forever()

if __name__ == "__main__":
    start_server()