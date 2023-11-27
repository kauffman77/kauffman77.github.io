/*
Language: interactive session
Author: Chris Kauffman <profk@umd.edu>
Description: simple interactive session with >> prompt and # comments
Category: scripting
*/

/** @type LanguageFn */
export default function(hljs) {
  // const VARIABLE = {
  //   className: 'variable',
  //   variants: [
  //     { begin: /\$[\w\d#@][\w\d_]*/ },
  //     { begin: /\$\{(.*?)\}/ }
  //   ]
  // };
  // const KEYWORDS = 'BEGIN END if else while do for in break continue delete next nextfile function func exit|10';
  return {
    name: 'interactive',
    keywords: { keyword: '' },
    contains: [
      hljs.HASH_COMMENT_MODE,
    ]
  };
}
