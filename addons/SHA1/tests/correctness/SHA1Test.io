
SHA1Test := UnitTest clone do(

	testBasic := method(
		correct := "20a9c9b806e488698415bb1bc52719e10f3d62b3"
		
		data := """Exercise your basic right
		
		digest := SHA1 clone
		digest appendSeq(data)
		v := digest sha1String

		assertEquals(v, correct)
	)
)
