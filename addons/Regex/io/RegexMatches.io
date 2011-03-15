//metadoc RegexMatches category Parsers
/*metadoc RegexMatches description
A regular expression match iterator.
*/

RegexMatches do(
	/*!doc RegexMatches reset
	Resets the search position to the beginning of the string. Returns self.
	*/
	reset := method(setPosition(0))

	/*!doc RegexMatches at(n) # debug usage
	Returns the n-th RegexMatch or nil if n is out of bounds
	*/
	at := method(n,
		i := 0; ret := nil
		self foreach(m,
			if (i == n , ret := m; break , i = i + 1)
		)
		ret
	)

	/*!doc RegexMatches asStrings # debug usage
	Returns the list of all matched strings
	*/
	asStrings := method(
		self all map(m,
					 self string exSlice(m range first, m range last))
	)

	/*!doc RegexMatches asStringAt(n) # debug usage
	Returns the n-th matched string or nil if n ist our of bounds
	*/
	asStringAt := method(n,
		i := 0; ret := nil
		self foreach(m,
			if (i == n ,
				ret := self string exSlice(m range first, m range last); break ,
				i = i + 1
		) )
		ret
	)

	/*!doc RegexMatches count # debug usage
	Returns the number of matches in the string
	*/
	count := method(i := 0; foreach(m, i = i + 1))

	/*doc RegexMatches last
	Returns the last match in the string.
	*/
	last := method(foreach(m, m))

	/*doc RegexMatches all
	Returns a list containing all matches in the string.
	*/
	all := method(map(m, m))

	/*doc RegexMatches map(value, message)
	Like <code>foreach</code>, but the result of each evaluation of <em>message</em> is returned
	in a list.
	*/
	map := method(
		output := list

		# (name, message)
		if (call argCount > 1,
			name := call argAt(0) name

			foreach(m,
				call sender setSlot(name, m)
				output append(call evalArgAt(1))
			)
			return output
		)

		# (message)
		msg := call argAt(0)
		foreach(m,
			output append(msg doInContext(m, call sender))
		)
		output
	)

	/*doc RegexMatches foreach(value, message)
	Loops through the matches, assigns each match to <em>value</em>, and evaluates <em>message</em>.
	Returns the result of the last evaluation.
	*/
	foreach := method(
		name := call argAt(0) name

		reset
		result := nil
		while(match := next,
			call sender setSlot(name, match)
			result := call evalArgAt(1)
		)
		result
	)

	/*doc RegexMatches foreachInterval(value, matchMessage, nonMatchMessage)
	Like <code>foreach</code>, but takes an extra message that will be evaluated for the non-matching
	text before each match, and the non-matching text after the last match.
	*/
	foreachInterval := method(
		name := call message argAt(0) name
		matchMessage := call message argAt(1)
		nonMatchMessage := call message argAt(2)

		cursor := 0
		foreach(match,
			if(match start > cursor,
				call sender setSlot(name, string exSlice(cursor, match start))
				call sender doMessage(nonMatchMessage)
			)
			call sender setSlot(name, match)
			call sender doMessage(matchMessage)
			cursor := match end
		)

		# Perform the inter-match interval for the tail end
		tail := string exSlice(cursor)
		if(tail size > 0,
			call sender setSlot(name, tail)
			call sender doMessage(nonMatchMessage)
		)

		self
	)

	/*doc RegexMatches replaceAllWith(templateString)
	Same as:
	<pre>
	replace(match, match expandTo(templateString))
	</pre>
	*/
	replaceAllWith := method(templateString,
		replace(m, m expandTo(templateString))
	)

	/*doc RegexMatches replace(name, message)
	Replaces each match in the string with the result of <em>message</em> and returns
	the resulting string.
	*/
	replace := method(
		name := call argAt(0) name

		parts := list
		foreachInterval(match,
			call sender setSlot(name, match)
			parts append(call evalArgAt(1))
			,
			parts append(match)
		)
		parts join
	)

	/*doc RegexMatches splitString
	Splits the string being matched against into pieces using the regex as the delimiter
	and returns the piece as a list of strings.
	*/
	splitString := method(
		parts := list
		cursor := 0
		foreach(match,
			parts append(string exSlice(cursor, match start))
			cursor = match end
		)

		s := string exSlice(cursor)
		parts append(s)
		parts
	)
)
