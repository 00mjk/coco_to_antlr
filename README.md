# coco_to_antlr

Convert your [Coco/R](http://ssw.jku.at/Coco/) attributed grammar
to an [ANTLR4](https://www.antlr.org/) one.
This tool automates most of the conversion (depending on the complexity of your
embedded instrumentation code):

- rewrite production rules to ANTLR parser productions
- rewrite Token definitions to ANTLR lexer rules
- rewrite `PRAGMAS` and `COMMENT` definitions to ANTLR lexer rules on `-> channel(HIDDEN)`
- rewrite CharSet definitions to `fragment` lexer rules
- copy embedded instrumentation code & (partially) adapt to different API
    - for C++, rewrite reference attributes to `@returns[]`
    - replace references to current/lookahead token `t`, `la` by `$ctx` (NOTE: these usually still need manual rewrite)
    - correctly reference arguments of the current scope (i.e. `@returns[int no]` needs to be assigned like `$no =`)

# TODO
See also the various TODO/FIXME comments in the source code, this list is only an excerpt from these

- `ANY` in Coco production rules has no equivalent in ANTLR
- character set definitions using set union & difference are not correctly rewritten
- `IF(...)` conflict resolvers work differently in ANTLR and have to be manually checked (are preserved as comments)
- *comments* are not preserved since version 67a4266 (when support for rule return attribute rewriting was implemented). Best way to preserve comments currently is to use version 784f8fd and the current master and merge the results (`git rebase` is your friend).
- name collisions of generated rule & attribute names with language keywords and/or ANTLR syntax are not checked (e.g. a rule `char` or instrumentation code using a reference to a rule `text` which collides with [`$text`](https://github.com/antlr/antlr4/blob/master/doc/actions.md#parser-rule-attributes), see <https://github.com/antlr/antlr4/issues/2266>).
- `NESTED` comment definitions are not translated (though they should be possible with recursive lexer rules)
- using an external lexer (i.e. only listing token names, not defining them) is not supported
- string/character escapes are partly converted, need manual checking
- Tokens with `CONTEXT` specification are not supported

- Test with instrumentation language other than C++ (see e.g. <https://github.com/antlr/antlr4/issues/2265>)
- Test on windows, linux only so far
- Rewrite Token & CharSet definitions with AST & Visitor, too, like productions already do
- Optimize code generation from AST (i.e. remove unneeded braces, especially for quantifiers around a single subrule, like `('TOKEN')?`)
- Parsing of (C++) attributes in rule definition and invocation is quite fragile
- `$` in instrumentation code fails ANTLR

