package yinet

import (
	"log"
	"net"
)

type YiTcpServer struct {
	Addr string
	ln   net.Listener
}

func New(addr string) YiTcpServer {
	server := new(Server)
	server.Addr = addr

	return server
}

func (self *YiTcpServer) Init() {
	ln, err := net.Listen("tcp", self.Addr)
	if err != nil {
		log.Fatal(err)
	}
	self.ln = ln
}

func (self *YiTcpServer) Run() {
	for {
		conn, err := self.ln.Accept()
		if err != nil {
			// todo
		}
		ss := NewSession(conn)

	}
	go func(c net.Conn) {
		// Echo all incoming data.
		io.Copy(c, c)
		// Shut down the connection.
		c.Close()
	}(conn)
}

type YiSession struct {
	conn net.Conn
}

func NewSession(conn *net.Conn) YiSession {
	ss := new(YiSession)
	ss.conn = conn
	return ss
}
