
SHA2 := "SHA2 provides SHA-256/384/512 digest algorithms"

File sha2String := method(
	digest := SHA1 clone
	buffer := Sequence clone

	openForReading
	while(isAtEnd not,
		readToBufferLength(buffer, 65536)
		digest appendSeq(buffer)
	)
	close
	digest sha2String
)

Sequence sha2String := method(
	SHA1 clone appendSeq(self) sha2String
)

Sequence sha2 := method(
	SHA1 clone appendSeq(self) sha2
)

Sequence hashString := Sequence getSlot("sha2String")
Sequence hash := Sequence getSlot("sha2")
