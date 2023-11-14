import subprocess
from http.server import BaseHTTPRequestHandler, HTTPServer
import os

# Create Global variable for request
#Request = None

# Create class to handle requests
class RequestHandler_httpd(BaseHTTPRequestHandler):
  def do_GET(self):
    #global Request
    check_path = 'Check.txt'
    Request = self.requestline
    Request = Request[5 : int(len(Request)-9)]
    print(Request)
    if Request == 'update':
      subprocess.run(["python", "Update.py"])
      if os.path.exists(check_path):
        messagetosend = bytes('failed',"utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(messagetosend))
        self.end_headers()
        self.wfile.write(messagetosend)
      else:
        messagetosend = bytes('success',"utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(messagetosend))
        self.end_headers()
        self.wfile.write(messagetosend)
    if Request == 'check':
      subprocess.run(["python", "Check_For_Update.py"])
      if os.path.exists(check_path):
        messagetosend = bytes('exist',"utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(messagetosend))
        self.end_headers()
        self.wfile.write(messagetosend)
      else:
        messagetosend = bytes('not',"utf")
        self.send_response(200)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(messagetosend))
        self.end_headers()
        self.wfile.write(messagetosend)
    return

server_address_httpd = ('192.168.6.149',8080) #Hotspot
#server_address_httpd = ('192.168.1.14',8080)
#server_address_httpd = ('192.168.1.9',8080) #Home
#server_address_httpd = ('10.145.14.174',8080) #ITI
httpd = HTTPServer(server_address_httpd, RequestHandler_httpd)
print('Starting server:')
httpd.serve_forever()


