# wordAnalysis
简单词法分析器

目标：实现从源程序中分出各种单词，区分出保留字、标识符、常数和运算符等符号。

流程：

  选用的是C语言来设计词法分析器，分析的语言也是C语言。
  
	C语言有32个保留字：
	
 	auto 	   break	     case		char		  const
	
        continue	   default	 do		    double	  else
	
        enum	   extern	 float	    for	      goto
	
        If	       int	     long		register	  return
	
        Short	   signed	 sizeof	    static	  struct
	
	Switch	   typedef	 union	    unsigned	  void
	
        Volatile	   while
	
	
	符号有：
	+ 	-	  >	  < 	= 	&	  |	  ~ 	^	  *	  / 	% 	!
	
        ?	  :	  , 	  .	  ;	  #	  '   "   [	  ] 	{ 	}	  (	  )
	
	+=  	  -=  	  >=   	 <=    	==   	&=  	 |=  	 ~=  	  ^=  	  *=  	  /= 	  %=  	  !=
	
	 ++   	  --   	  >>     <<     ->       &&      ||         
		    
  1)	输入一段程序，以‘$’美元符号结尾，用字符数组prog保存，最大长度为2000；
  
  2)	用token保存扫描到的单词，ch表示当前读到的字符，p表示数组的下标指针。m表示token的下标，数组number用来保存常量。
  
  3)	对prog进行扫描（用scanner函数），在do-while循环中，每扫描一次返回一个标志syn。a) 若syn为0表示读到结尾，结束循环。
  
  b) 若syn在1-32之间，表示读到的单词是保留字。
  
  c) 若syn为48表示读到了标识符，将单词插入到标识符表mark中。
  
  d) 若syn为49表示读到的是数字，将常数插入到常数表中。
  
  e) 若syn在50-96之间表示读到了符号。
  
  f) 若syn为-1，表示读到错误字符。
