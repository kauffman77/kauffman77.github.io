function interactive_lang() {      // define a simple interactive language
  return {
    name: 'interactive',           // language name
    keywords: {
      $pattern: /[^ \t\n]+/,       // lex based on non-whitespace
      keyword: [">>","(shellac)"], // allowed interactive prompts
    },
    contains: [
      // hljs.HASH_COMMENT_MODE,      // use standard hash comments
      hljs.COMMENT(/# /, /$/),
    ]
  };
}
hljs.registerLanguage('interactive', interactive_lang);


hljs.COMMENT(/# /, /$/)
