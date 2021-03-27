# Parser

This is an implementation of a recursive descent parser for mathematical expressions.
The parser only handles the following input:
- numbers (non decimal)
- spaces
- (
- )
- \+
- \*

The grammar for this parser is:
```
E -> TE`
E -> T
E`-> + TE`
E`-> (END)`
T -> NT`
T -> N
T`-> * NT`
T`-> (END)
N -> Int
N -> (E)
```

# How to use:
Use `make run` to start the program<br />
At the prompt enter math expression to evaluate. Ex: `1+1*2` or `(1+2)*(3+4)`<br />
To exit use ctrl-C<br />
