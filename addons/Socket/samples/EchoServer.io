#!/usr/bin/env io

Echo := Object clone do(
    handleSocketFromServer := method(socket, aServer,
		writeln("[Got echo connection from ", socket address address, "]")
		socket setReadTimeout(60*60)
		while(socket isOpen,
			if(socket read,
				data := socket readBuffer
				writeln(socket address address, " ", data)
				socket write(data)
			)
			socket readBuffer empty
		)
		writeln("[Closed ", socket address address, "]")
    )
)

server := Server clone do(
	setPort(8456)
	handleSocket := method(socket,
		Echo clone @handleSocketFromServer(socket, self)
	)
)

writeln("[Starting echo server on port 8456]")
server start
