AddressFamily do(
	AF_UNIX := 1
	AF_INET := 2

	families := Map with(AF_UNIX asString, UnixPath clone, AF_INET asString, IPAddress clone)

	with := method(family, AddressFamily clone setAddress(families at(family asString) clone))

	forward := method(
		address performWithArgList(call message name, call message argsEvaluatedIn(call sender))
	)
)