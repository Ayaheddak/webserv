#!/usr/bin/env python

print("Content-type: text/html")
print()

# Retrieve the values from the query string
import cgi
form = cgi.FieldStorage()
num1 = int(form.getvalue("num1"))
num2 = int(form.getvalue("num2"))

# Perform the addition
result = num1 + num2

# Print the HTML response
print("<html>")
print("<head>")
print("<title>Addition Result</title>")
print("</head>")
print("<body>")
print("<h1>Addition Result:</h1>")
print("<p>{0} + {1} = {2}</p>".format(num1, num2, result))
print("</body>")
print("</html>")
