package main

import (
	"net"
	"time"
)

func main() {
	l,err := net.Listen("tcp",":8080")
	if err != nil {panic(err)}
	c,cerr:= l.Accept()
	if cerr != nil {panic(err)}
	defer c.Close()
	defer l.Close()
	
	
	t = time.Now()
	var buf = make([]byte,102400000)
	n,rerr := c.Read(buf)
	if rerr != nil {
		panic(rerr)
	}
	println("time: ",time.Now().Sub(t).Seconds())
	println("done! size: ",n,"bytes")
}