#!/usr/bin/env io


m := EmailMessage clone
m setFrom("bar@bar.com")
m setTo("wasi.network@gmail.com")
m setSubject("hello")
m setContent("This is a test.")
m send

