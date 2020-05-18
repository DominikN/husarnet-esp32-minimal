import socket

with socket.socket(socket.AF_INET6, socket.SOCK_STREAM) as s:
	s.bind((socket.gethostname(), 8002))
	s.listen(1)
	conn, addr = s.accept()
	with conn:
		print('Connected by', addr)
		while True:
			data = conn.recv(1024)
			if not data: break
			print(data.decode('ascii'))
