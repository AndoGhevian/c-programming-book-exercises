/* clip the content to fit appropriate len.

returns length of clipped part if
assumed clipping performed on a str
by skipping first clipskip characters,
putting in the middle placeholder of clipperlen
length and leaving at the end required
cliprest number of characters.
if provided str is shorter than
"clipskip + clipperlen + cliprest", then no clipping
performed, and returns 0.

clipskip -> how many characters to skip before clip.
clipperlen -> expected placeholder length.
cliprest -> number of characters to show after clip.

all are non negative numbers.

note: trimming/clipping is about how to fit some content
exceeding maximum content length limit inside smaller space.
it will not make scense to show longer content when limit
exceeded.

example for max limit of 2 characters:
ab -> is ok
abc -> a...c, no scense, here we can even have 2 more characters
  than needed.
a.c -> is okt

extra:
if you want, you can replace clipper with something longer, or shorter
so eventually this function is able to close all use cases one
can think of.
*/
int strclip(char *, int, int, int);
