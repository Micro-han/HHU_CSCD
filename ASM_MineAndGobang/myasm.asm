DATA	SEGMENT
MINE	DB 256 DUP(' ')																						;放置程序生成的扫雷界面(不给用户显示)
DISMINE DB 256 DUP(' ') 																					;放置用户已玩的扫雷界面(给用户显示)					
MINEL	DB 70 DUP(' ') 	 																					;用于显示扫雷界面
SPRMINE DB 256 DUP(' ')       																				;用于递归扩散赋值为0的点
RO_CO	DB 6, 0, 6 DUP(?) 																					;用于用户输入的行数和列数
STA_T 	DW 0 																								;用于记录开始游戏的时间
NUM16 	DB '1', '2', '3', '4', '5', '6', '7', '8', '9', '1', '1', '1', '1', '1', '1', '1' 					;用户显示行数
TIP216	DB '   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |16 ', 0DH, 0AH, '$' 			;用于显示列数
TIP3	DB '--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --', 0DH, 0AH, '$' 				;用户显示横线分割
TIP4    DB '   PLEASE INPUT YOUR POSITION(X,Y)  EG(10,6)     ', 0DH, 0AH,'$'
TIP5 	DB 'THE POINT HAS BEEN OCCUPIED !!!', 0DH, 0AH, '$'
TIP6 	DB 'INPUT FORMAT IS UNCORRECT!!!', 0DH, 0AH, '$'
TIP7 	DB '*********************', 0DH, 0AH
        DB '                     ', 0DH, 0AH
        DB '   YOU ARE BOOM!!!   ', 0DH, 0AH
        DB '                     ', 0DH, 0AH
        DB '*********************', 0DH, 0AH,'$'
TIP8 	DB '*********************', 0DH, 0AH
        DB '                     ', 0DH, 0AH
        DB '   YOU ARE WIN!!!!   ', 0DH, 0AH
        DB '                     ', 0DH, 0AH
        DB '*********************', 0DH, 0AH,'$'
TIP9    DB '   PLEASE INPUT YOUR OPERATION(0:FOUND,1:MARK)   ', 0DH, 0AH,'$'
TIP10   DB '                    The remaining Minutes:', '$'
TIP11   DB '************************', 0DH, 0AH
        DB '                        ', 0DH, 0AH
        DB '   YOU ARE OVERTIME!!!  ', 0DH, 0AH
        DB '                        ', 0DH, 0AH
        DB '************************', 0DH, 0AH,'$'
TIP12	DB 'PLEASE INPUT THE SIZE:(10-16): $ '
TIP13	DB 'PLEASE INPUT THE NUM OF MINES(10-99): $ '
DATA1	DB 255 DUP('$')
DATA2	DB 255 DUP('$')
KONG 	DB 0DH, 0AH, '$'
CHESSBOARD DB 218,13 DUP(194),191,13 DUP(195,13 DUP(197),180),192,13 DUP(193),217 	;设置棋盘的缓冲区
X DB 0										;落子坐标 x
Y DB 0                                                        						;落子坐标 y
MY DB 1										;我的坐标是1，对方的坐标是2
FLAG DB 0									;判断是否可以落子的标记，1为可以，0为不可以
STATE DB 0									;目前的状态，单机：0为游戏进行中，2为一方退出；3为一方获胜
											;0该我下，1我已经下完，等待接受X；2等待接受Y；4对方获胜，5对方退出
OVER DB 0									;判断是否比赛结束，CALL ISWIN 0为没有结束，1为结束。结束时，最后落子方获胜
LED DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH     					;七段数码管对应显示
S1 DB 0                             									;用于保存输入坐标值x
S2 DB 0										;用于保存输入坐标值y
TEMP DB 0                          	 								;单机时判断该下黑子还是白子
ORDER DB 1                          								;双机时标志先手or后手，1表示先手，2表示后手
TI DB ' 1 2 3 4 5 6 7 8 9 a b c d e f',0AH,0DH,'$'						;棋盘的y坐标
ERROR2 DB 'YOU CANNOT PUT HERE!',0AH,0DH,'$' 						;报错,"你不能放在这里"
WRONG DB 0AH,0DH,'FALSE INPUT!',0AH,0DH,'$'						;错误信息的提示
CLEAN DB 72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,72 DUP(32),0AH,0DH,'$';更新棋盘
PUT DB 'PLEASE INPUT THE POSITION(X Y):',0AH,0DH,'$'						;请输入棋子的位置(x,y)
GAMEEND DB 'ONE PLAYER HAS WIN!',0AH,0DH,'$'						;游戏结束信息提示
CONGRA DB 'YOU WIN! CONGRATULATIONS!',0AH,0DH,'$'					;游戏提示信息,"恭喜!你赢了!"
SORRY DB 'YOU LOSE! DONNOT GIVE UP!',0AH,0DH,'$'						;游戏提示信息,"对不起,你输了,不要放弃!"
WAIT1 DB 'PLEASE WAIT...',0AH,0DH,'$'  							;进入等待信息提示 
CHOOSE DB 'PLEASE CHOOSE GAME MODEL:(1 FOR ONE PLAYER, 2 FOR TWO PLAYERS, ESC TO QUIT)',0AH,0DH,'$'	;选择游戏的玩法
EXIT DB 'ONE PLAYER HAS QUIT!',0AH,0DH,'$'						
PLN		DB 0DH, 0AH, '$'
SEED10	DB 10 DUP(0)
SEED80	DB 80 DUP(0)
BUFF1    DB '********************************************************', 0DH, 0AH
         DB '                                                        ', 0DH, 0AH
         DB '   INPUT THE GAME YOU WANT TO PLAY(0:GOBANG, 1:SWEEP)   ', 0DH, 0AH
         DB '                                                        ', 0DH, 0AH
         DB '********************************************************', 0DH, 0AH,'$'
DATA	ENDS

STACK	SEGMENT
		DB 200 DUP(?)
STACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA, SS:STACK
START:	
		
		MOV AX, DATA
		MOV DS, AX
		MOV ES, AX
		MOV AX, STACK
		MOV SS, AX	
		
		LEA DX,BUFF1      
        MOV AH,09H                 
        INT 21H
	
		MOV AH,1
		INT 21H      ;输入选择字符
		SUB AL,30H
		CMP AL, 1
		
		LEA DX,KONG	      
        MOV AH,09H                 
        INT 21H
		JZ 	DO1	;扫雷
		JMP	DO2 ;五子棋
		
DO1:
		LEA DX, TIP12									;输出提示信息
		MOV AH, 09H
		INT 21H      
		
		LEA DX,	DATA1    								;输入棋盘大小
		MOV AH, 0AH
		INT 21H
		LEA DX, KONG
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIP13
		MOV AH, 09H
		INT 21H
		LEA DX,	DATA2    								;输入棋盘大小
		MOV AH, 0AH
		INT 21H
		LEA DX, KONG
		MOV AH, 09H
		INT 21H     								 	;存入雷的数量

		CALL SEED 										;生成80个随机数种子
		CALL LAYM 										;布雷
		CALL LAYN										;给非雷区赋值	
						
		CALL GET_T		 								;获取当前时间

		LEA DX, KONG 									;游戏提示
		MOV AH, 09H
		INT 21H
SHOW_I:											
		LEA DX, PLN 									;换行
		MOV AH, 09H
		INT 21H
							
		LEA DX, TIP216  									;输出行数
		MOV AH, 09H
		INT 21H
														
		LEA DX, TIP3 									;横线分割
		MOV AH, 09H
		INT 21H

		CALL SHOWM 										;展示界面
															
		LEA DX, PLN										;换行
		MOV AH, 09H
		INT 21H

		PUSH BX
		CALL REM_T                                      ;得到还剩下多少时间

		CMP BX, 3030H
		JZ TIME_OUT_1

		LEA DX, TIP10  									;显示还剩下多少时间
		MOV AH, 09H
		INT 21H
		MOV DL, BH 										;输出十位数
		MOV AH, 2
		INT 21H
		MOV DL, BL 										;输出个位数
		MOV AH, 2
		INT 21H
		POP BX

		LEA DX, PLN										;换行
		MOV AH, 09H
		INT 21H

INPUT:
		LEA DX, TIP9									;提示输入是要标记还是探测雷
		MOV AH, 09H
		INT 21H

		MOV AH, 1										;提示是要标记还是探测雷,1为标记,0为探测
		INT 21H
		MOV AH, 0 										;将AX高八位清零
		PUSH AX 										;将输入结果压栈保存
		CMP AL, '0'
		JZ CORRECT
		CMP AL, '1'
		JZ CORRECT
		JMP ERROR	
CORRECT:
		LEA DX, PLN 									;换行
		MOV AH, 09H
		INT 21H
	
		LEA DX, TIP4									;提示输入行数
		MOV AH, 09H
		INT 21H

		PUSH BX 										;判断是否超时
		CALL REM_T                                      ;得到还剩下多少时间

		CMP BX, 3030H
		JZ TIME_OUT_1

		POP BX

		LEA DX, RO_CO
		MOV AH, 0AH
		INT 21H
		MOV CX, 0
		MOV CL, RO_CO+1 								;实际输入的字符数送CL
		ADD DX, 2                                       ;将DX指向用户输入的第一个字符
		MOV DI, DX
		PUSH CX
		MOV AL, ','
		CLD
		REPNZ SCASB
		JZ FOUND
		POP CX
		JMP ERROR

TIME_OUT_1:
		JMP TIME_OUT_2

FOUND:
		POP CX
		SUB DI, DX 										;逗号','关键字在第DI-DX个
		MOV BX, DI 										;次数保存在BX中
		MOV CH, BL 										;次数保存在CH中
		SUB CL, CH 										;总长度减去逗号的位置,等于逗号后面有几个字符
		DEC CH 											;得到:逗号前面有CH个字符,逗号后面有CL个字符
		MOV DI, DX                                      ;还原DI
        
        MOV AL, BYTE PTR [DI] 							;得到用户输入的第一行数
        ADD DI, 1
        SUB AL, 48                						;48为0的ASCLL码值
        DEC CH
        CMP CH, 0
        JZ GET_CO 										;如果CH为0,代表行数小于10
        												;如果CH不为0,代表行数大于10
		MOV AL, 10 										;令AL为10
		MOV AH, BYTE PTR [DI] 							;得到第二个行数
		ADD DI, 1
		SUB AH, 48 										;48为0的ASCLL码值
		ADD AL, AH 										;行数放在AL
		MOV AH, 0
		JMP GET_CO

GET_CO:													;取列数
		ADD DI, 1 										;DI加一,跳过逗号
		MOV BL, BYTE PTR [DI] 							;得到用户输入的第一列数
        ADD DI, 1
        SUB BL, 48                						;48为0的ASCLL码值
        MOV AH, BL 										;将列数放在AH
        DEC CL
        CMP CL, 0
        JZ IN_END 										;如果CL为0,代表列数小于10,结束输入
        												;如果CL不为0,代表列数大于10
		MOV BL, 10 										;令BL为10
		MOV BH, BYTE PTR [DI] 							;得到第二个列数
		ADD DI, 1
		SUB BH, 48 										;48为0的ASCLL码值
		ADD BL, BH
		MOV AH, BL 										;将列数放在AH
		JMP IN_END

IN_END:													;输入结束,行数放在AL,将列数放在AH
;		CALL DISHEX
		CMP AL, 16                 						;做行数是否溢出判断
		JG ERROR
		CMP AL, 0										;做行数是否溢出判断
		JL ERROR
		CMP AH, 16  									;做列数是否溢出判断
		JG ERROR
		CMP AH, 0 										;做列数是否溢出判断
		JL ERROR
		MOV CX, 0                                       
		MOV BX, AX 										;备份一份(行数放在BL,将列数放在BH)
		MOV DX, AX 										;再备份一份(行数放在DL,将列数放在DH),为递归扩散准备
		DEC AL 											;计算公式为:(行数AL-1)*16+(列数AH-1)
		DEC BH
		MOV BL, BH 										;将列数放在BL
		MOV BH, 0
		MOV CL, 16
		MUL CL
		ADD BX, AX 										;得到最终结果,放在BX中

		POP CX 											;将用户输入的是探测还是标记赋值给CX
		CMP CL, '0'
		JZ DETECT 										;如果为0,则代表用户想要去探测雷
		LEA DI, DISMINE 								;取显示地雷棋盘的偏移地址
		CMP [DI+BX], BYTE PTR ' '
		JNZ SHOWN 										;如果输入的区域不等于' ',则代表此处已经显示过
		MOV [DI+BX], BYTE PTR 'x' 						;否则做x标记
		JMP SHOW_I

TIME_OUT_2:
		JMP TIME_OUT

DETECT:
		LEA DI, MINE 									;取地雷棋盘的偏移地址
		MOV AL, [DI+BX] 								;取出此处的值
		CMP [DI+BX], BYTE PTR '*'
		JZ G_OVER 										;如果踩到地雷,则游戏结束

		LEA DI, DISMINE 								;取显示地雷棋盘的偏移地址
		CMP [DI+BX], BYTE PTR ' '
		JNZ MARKED 										;如果输入的区域不等于' ',则判断是否为'x'
		JMP IS_ZERO 									;等于'+',则判断是否为0
MARKED:
		CMP [DI+BX], BYTE PTR 'x'
		JNZ SHOWN 										;如果输入的区域不等于'x',则代表此处已经显示过
IS_ZERO:
		CMP AL, '0' 									;此位置的值与0相比
		JZ SPREAD_P 									;如果为0,则需要递归扩散(spread)此位置的其他为0的点
		MOV [DI+BX], AL									;执行该区域显示
		CALL IS_WIN 									;判断是否赢得游戏

		LEA DX, PLN										;换行
		MOV AH, 09H
		INT 21H

		JMP SHOW_I

SPREAD_P:
		CALL SPREAD          							;递归扩散(spread)
		CALL IS_WIN 									;判断是否赢得游戏
		JMP SHOW_I

ERROR:
		LEA DX, PLN  									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, PLN  									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, TIP6 									;显示输入格式不正确
		MOV AH, 09H
		INT 21H
		PUSH AX 										;将保存的判断出栈
		JMP SHOW_I

SHOWN:	
		LEA DX, PLN  									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, PLN  									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, TIP5 									;显示此处已显示
		MOV AH, 09H
		INT 21H
		PUSH AX 										;将保存的判断出栈
		JMP SHOW_I

G_OVER:
		LEA DX, PLN 									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, PLN  									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, TIP7 									;显示游戏结束
		MOV AH, 09H
		INT 21H
		LEA DX, TIP7 									;显示游戏结束
		MOV AH, 09H
		INT 21H
		LEA DX, TIP7 									;显示游戏结束
		MOV AH, 09H
		INT 21H
		JMP END_GAME

TIME_OUT:
		LEA DX, PLN 									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, PLN  									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, TIP11 									;显示时间超时
		MOV AH, 09H
		INT 21H
		LEA DX, TIP11 									;显示时间超时
		MOV AH, 09H
		INT 21H
		LEA DX, TIP11 									;显示时间超时
		MOV AH, 09H
		INT 21H
		JMP END_GAME

END_GAME:
		MOV AH,4CH
     	INT 21H

;游戏胜利条件判断
;当DISMINE中所有的的' '或者'x'都是地雷时胜利
;
IS_WIN	PROC NEAR
		PUSH DX
		PUSH CX
		PUSH BX
		PUSH AX
		PUSH DI
		PUSH SI
		LEA DI, DISMINE 								;将DISMINE的偏移地址给DI
		LEA SI, MINE 									;将MINE的偏移地址给SI
		MOV BX, 0
		MOV CX, 0

IS_UNSHOW:
		MOV CX, 1
		CMP [DI+BX], BYTE PTR ' ' 						;如果等于' '
		JZ IS_MINE
IS_MARK:
		MOV CX, 2
		CMP [DI+BX], BYTE PTR 'x'
		JZ IS_MINE
NEXT_P:
		ADD BX, 1 										;BX指向下一个点
		CMP BX, 256 									;如果BX为256,代表遍及结束
		JZ YOU_WIN 										;游戏胜利
		JMP IS_UNSHOW 									;继续检测
IS_MINE:
		CMP [SI+BX], BYTE PTR '*'
		JNZ IS_DONE 									;如果有一个地方不是地雷,则判断结束
		CMP CX, 1
		JZ IS_MARK 										;如果是1已经判断过是否显示过了,接下来判断是否为标记的
		JMP NEXT_P 										;如果不是1则是2,表示两种情况都已经判断过了,直接判断下一个点
 
YOU_WIN:
		 												;将棋盘显示出来
		MOV CX, 256
		CLD
		REP MOVSB

		LEA DX, PLN 									;换行
		MOV AH, 09H
		INT 21H

		LEA DX, PLN 									;换行
		MOV AH, 09H
		INT 21H
								
		LEA DX, TIP216  									;输出行数
		MOV AH, 09H
		INT 21H
														
		LEA DX, TIP3 									;横线分割
		MOV AH, 09H
		INT 21H

		CALL SHOWM 										;展示界面												
		LEA DX, PLN										;换行
		MOV AH, 09H
		INT 21H

		PUSH BX
		CALL REM_T                                      ;得到还剩下多少时间

		LEA DX, TIP10  									;显示还剩下多少时间
		MOV AH, 09H
		INT 21H
		MOV DL, BH 										;输出十位数
		MOV AH, 2
		INT 21H
		MOV DL, BL 										;输出个位数
		MOV AH, 2
		INT 21H
		POP BX

		LEA DX, PLN										;换行
		MOV AH, 09H
		INT 21H

		LEA DX, TIP8 									;显示胜利
		MOV AH, 09H
		INT 21H
		
		LEA DX, TIP8 									;显示胜利
		MOV AH, 09H
		INT 21H		

		LEA DX, TIP8 									;显示胜利
		MOV AH, 09H
		INT 21H

		MOV AH,4CH
     	INT 21H
IS_DONE:
		POP SI
		POP DI
		POP AX
		POP BX
		POP CX
		POP DX
		RET
IS_WIN 	ENDP

;
;此子程序为当用户输入的点的值为0,则需要递归扩散(spread)此位置的其他为0的点
;
;基本思想为:建立一个新的矩阵SPRMINE，这个矩阵刚开始的值与MINE完全一致，
;			然后在矩阵SPRMINE先扩散第一个为0的点周围的8个点，
;			将这八个点中每一个为0的点压栈，并且在DISMINE中将这些不为0的点的值显示出来，
;			然后将此点的值赋值为‘9’（由于矩阵中元素的可能取值只能为：雷/0/1/2/3/4/5/6/7/8），
;			赋值为‘9’代表这个点已经被扩散过了，
;			当下一个点想要扩散此点的时候，发现此点的值已经不为‘0’了，于是就会跳过此点，不会重复扩散此点，
;			并且在DISMINE中将此点赋值为0，
;			第一个为0的点扩散完全后，从栈中取出栈顶元素的点，然后继续对此点进行同样的操作，直到栈中没有点为止。
;扩散方向为:上、上右、右、右下、下、左下、左、左上
;
SPREAD	PROC NEAR
		PUSH DX
		PUSH CX
		PUSH BX
		PUSH AX
		PUSH DI
		PUSH SI

		MOV CX, '-'
		PUSH CX 										;用'-'作为递归结束
														;先将SPRMINE初始化
		LEA SI, MINE 									;将MINE的偏移地址给SI
		LEA DI, SPRMINE         						;将SPRMINE的偏移地址给DI
		MOV CX, 256 									;256个点
		CLD
		REP MOVSB	 									;初始化完成
LOOP_SP:
		MOV AX, BX  									;将BX备份一份
		LEA SI, DISMINE 								;将DISMINE的偏移地址给SI
		LEA DI, SPRMINE 								;将SPRMINE的偏移地址给DI,为递归扩散做准备
		CMP BYTE PTR [DI+BX], '0' 						;查看此点是否为0
		JNZ SP_NEXT1                                   	;不是0证明此点已经被遍历过,则跳转到下一次结点LOOP_SP0

;DX中(行数放在DL,将列数放在DH),范围都是1~16
SP_U:													;查看上结点
		MOV BX, AX 										;将BX还原
		CMP DL, 1 										;如果行数为第一行,则无上结点
		JZ SP_RU 										;则跳转到右上结点
		SUB BX, 16 										;BX减16,到上结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL  								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;上结点与0做比较
		JNZ SP_RU 										;不为0跳转到右上结点
		PUSH BX          								;为0则将这个点入栈
SP_RU:													;查看右上结点
		MOV BX, AX 										;将BX还原
		CMP DL, 1 										;如果行数为第一行,则无上结点
		JZ SP_R 										;则跳转到右结点
		CMP DH, 16 										;如果列数为最后一列,则无右结点
		JZ SP_R 										;则跳转到右结点
		SUB BX, 15 										;BX减15,到右上结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL   								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;右上结点与0做比较
		JNZ SP_R										;不为0跳转到右结点
		PUSH BX          								;为0则将这个点入栈
SP_R:													;查看右结点
		MOV BX, AX 										;将BX还原
		CMP DH, 16 										;如果列数为最后一列,则无右结点
		JZ SP_RD 										;则跳转到右下结点
		ADD BX, 1 										;BX加1,到右结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL 								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;右结点与0做比较
		JNZ SP_RD										;不为0跳转到右下结点
		PUSH BX          								;为0则将这个点入栈
		JMP SP_RD

SP_NEXT1: 												;临时跳转
		JMP SP_NEXT2

SP_RD:													;查看右下结点
		MOV BX, AX 										;将BX还原
		CMP DL, 16 										;如果行数为最后一行,则无下结点
		JZ SP_D 										;则跳转到下结点
		CMP DH, 16 										;如果列数为最后一列,则无右结点
		JZ SP_D 										;则跳转到下结点
		ADD BX, 17 										;BX加17,到右下结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL   								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;右上结点与0做比较
		JNZ SP_D										;不为0跳转到右结点
		PUSH BX  										;为0则将这个点入栈
		JMP SP_D

SP_D:													;查看下结点
		MOV BX, AX 										;将BX还原
		CMP DL, 16 										;如果行数为最后一行,则无下结点
		JZ SP_LD 										;则跳转到左下结点
		ADD BX, 16										;BX加16,到下结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL   								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI


		CMP BYTE PTR [DI+BX], '0' 						;右上结点与0做比较
		JNZ SP_LD										;不为0跳转到左下结点
		PUSH BX  										;为0则将这个点入栈
		JMP SP_LD

		SP_NEXT2: 										;临时跳转
		JMP SP_NEXT

SP_LD:													;查看左下结点
		MOV BX, AX 										;将BX还原
		CMP DL, 16 										;如果行数为最后一行,则无下结点
		JZ SP_L 										;则跳转到左结点
		CMP DH, 1 										;如果列数为第一列,则无左结点
		JZ SP_L 										;则跳转到左结点
		ADD BX, 15 										;BX加15,到左下结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL  								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;右上结点与0做比较
		JNZ SP_L										;不为0跳转到左结点
		PUSH BX  										;为0则将这个点入栈
SP_L:													;查看左结点
		MOV BX, AX 										;将BX还原
		CMP DH, 1 										;如果列数为第一列,则无左结点
		JZ SP_LU										;则跳转到左上结点
		SUB BX, 1 										;BX减1,到左结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL   								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;右上结点与0做比较
		JNZ SP_LU										;不为0跳转到左上结点
		PUSH BX  										;为0则将这个点入栈
SP_LU:													;查看左上结点
		MOV BX, AX 										;将BX还原
		CMP DL, 1 										;如果行数为第一行,则无上结点
		JZ SP_NEXT 										;则跳转到SP_NEXT
		CMP DH, 1 										;如果列数为第一列,则无左结点
		JZ SP_NEXT										;则跳转到SP_NEXT
		SUB BX, 17 										;BX减15,到左上结点

		LEA DI, MINE
		PUSH AX 										;暂存AX
		MOV AL, [DI+BX] 								;将MINE中这个点的值取出来,赋值给AX
		MOV [SI+BX], AL   								;将DISMINE中这个点为的值赋值伪AX
		POP AX 											;还原AX
		LEA DI, SPRMINE 								;还原DI

		CMP BYTE PTR [DI+BX], '0' 						;左上结点与0做比较
		JNZ SP_NEXT										;不为0跳转到SP_NEXT
		PUSH BX  										;为0则将这个点入栈
SP_NEXT:
		MOV BX, AX 										;将BX还原
		LEA DI, SPRMINE
		MOV [DI+BX], BYTE PTR '9'   					;将SPRMINE中这个点赋值为'9'
		LEA SI, DISMINE
		MOV [SI+BX], BYTE PTR '0'   					;将DISMINE中这个点赋值为'0'
		POP BX
		CMP BX, '-' 									;如果BX为'-',代表递归结束
		JZ SP_DONE
														;计算新结点的行数(DL)和列数(DH)
		PUSH AX
		PUSH CX                                         ;保存两个数
		MOV AX, BX										;将BX赋值给AX
		MOV CL, 16
		DIV CL
		ADD AH, 1										;余数在AH,代表多少列,再加一
		ADD	AL, 1 										;商放在AL,代表多少行,再加一
		MOV DX, AX 										;赋值给DX
		POP CX
		POP AX 											;还原两个数	

		JMP LOOP_SP

SP_DONE:
		POP SI
		POP DI
		POP AX
		POP BX
		POP CX
		POP DX
		RET
SPREAD 	ENDP

;
;此子程序为显示扫雷界面
;
SHOWM 	PROC NEAR 
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH DI
		PUSH SI
		MOV CX, 0										;将CX赋初值为0,记录多少行
		LEA SI, DISMINE 								;取DISMINE的偏移地址
PRINT2:
		LEA DI, MINEL									;取MINEL的偏移地址
		INC CX 											;行数加一
		MOV BX, 1										;将CX赋初值为1,记录多少列

		;将MINEL前3个字节赋值为'(CX)'、' '、' ',并且将DI指向第4个字节
		PUSH SI
		LEA SI, NUM16
		ADD SI, CX
		DEC SI
		CLD
		MOVSB
		CMP CX, 10
		JZ	LOOP_S10 									;如果CX为10,则后面输出0
		CMP CX, 11
		JZ	LOOP_S11 									;如果CX为10,则后面输出1
		CMP CX, 12
		JZ	LOOP_S12 									;如果CX为10,则后面输出2
		CMP CX, 13
		JZ	LOOP_S13 									;如果CX为10,则后面输出3
		CMP CX, 14
		JZ	LOOP_S14 									;如果CX为10,则后面输出4
		CMP CX, 15
		JZ	LOOP_S15 									;如果CX为10,则后面输出5
		CMP CX, 16
		JZ	LOOP_S16 									;如果CX为10,则后面输出6
		MOV [DI], BYTE PTR ' '
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S

LOOP_S10:
		MOV [DI], BYTE PTR '0'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S
LOOP_S11:
		MOV [DI], BYTE PTR '1'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S

PRINT_S: 												;做临时跳转
		JMP PRINT2

LOOP_S12:
		MOV [DI], BYTE PTR '2'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S
LOOP_S13:
		MOV [DI], BYTE PTR '3'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S
LOOP_S14:
		MOV [DI], BYTE PTR '4'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S
LOOP_S15:
		MOV [DI], BYTE PTR '5'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S
LOOP_S16:
		MOV [DI], BYTE PTR '6'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		POP SI
		JMP LOOP_S

LOOP_S:
		MOV [DI], BYTE PTR '|'
		INC DI
		MOV [DI], BYTE PTR ' '
		INC DI
		CLD
		MOVSB											;将DISMINE的一个数赋值给MINEL
		INC BX 											;BX指向下一列
		MOV [DI], BYTE PTR ' '
		INC DI
		CMP BX, 17
		JNZ LOOP_S

		MOV BYTE PTR [DI], 0DH
		MOV BYTE PTR [DI+1], 0AH
		MOV BYTE PTR [DI+2], BYTE PTR '$'
		LEA DX, MINEL
		MOV AH, 09H										;调用9号字符串显示功能
		INT 21H
														;		横线分割
;		LEA DX, TIP3
;		MOV AH, 09H
;		INT 21H
		
		CMP CX, 16 										
		JNZ PRINT_S

		POP SI
		POP DI
		POP DX
		POP BX
		POP CX
		POP AX
		RET
SHOWM 	ENDP

;
;此子程序为布雷程序
;
;左上角为坐标原点,水平向右为X正方向,水平向左为Y正方向
;其中X坐标存于BH,Y坐标存于BL
;由于种子经过处理后产生的结果为0~15,所以XY坐标对应的位置为:[MINE]+Y*16+X 即:[MINE]+BL*16+BH
;
;从SEED80种子池中获取随机的XY左边策略为:
;
;

LAYM	PROC NEAR
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH SI
		PUSH DI

		MOV CH, 0									
		;MOV BL, [DATA2+2];雷的数量
		;SUB BL, '0'
		;MOV BH, [DATA2+3];
		;SUB BH, '0'
		;MUL BL, 10
		;ADD BL, BH
		
		MOV DX, 10										;16*16的界面总共CX个雷
		LEA DI, MINE 									;将MINE的偏移地址给DI
		LEA SI, SEED80          						;将SEED80的偏移地址给SI
		
		CMP CH, 0                                       ;CH为0代表第一次,直接开始获取位置
		JZ GETP1

HSEED80: 												;80个种子处理完之后,地雷没布满,则对80个种子每个循环右移3位
		MOV CH, 0
		MOV BX, 0
AGAINE:	
		MOV AX, [SI+BX]
		MOV CL, 3
		ROR AX, CL
		MOV [SI+BX], AX
		INC BX
		CMP BX,80
		JNZ AGAINE
		JMP GETP
GETP1:
		PUSH DX 										;暂存DX
GETP:
		MOV BX, 0
		MOV BL, CH
		PUSH CX
		MOV AX, [SI+BX]
		MOV DX, 0                                       ;为了防止商溢出,使用16位除法,DX(高16位)+AX(低16位)/CX.商:AX,余数:DX
		MOV CX, 16                             			;除16，产生0~15余数
       	DIV CX

       	MOV BH, DL										;余数放至BH作为X
       	PUSH BX 										;暂存BX(主要是BH)
       	MOV BH, 0
       	MOV BL, CH

       	ADD BX, AX 										;CH+AL[CH加上商]
       	MOV AX, BX 										;防止BX超过80,所以每次都要对BX进行除以80,然后取余
       	MOV BL, 80
       	DIV BL
       	MOV BL, AH 										;AH放除以80后的商,继续放回BL
       	MOV BH, 0 										;BX高八位清零
       	MOV AX, [SI+BX] 								;Y等于第[CH加上商]位种子除以16的余数
       	POP BX 											;还原BX
       	MOV DX, 0                                       ;DX清零,使除法运算不被影响
       	MOV CX, 16                             			;除16，产生0~15余数
       	DIV CX
       	MOV BL, DL

        POP CX
       	INC CH

       	CMP CH, 80 										;如果CH为80
       	JZ HSEED80 										;对种子进行处理	

		CALL HAVEM										;检查随机生成的坐标处是否已经存在雷
		CMP AX, 0										;如果有地雷,则AX=0
		JZ GETP
														;保存雷操作
		MOV DH, 0										;将DX高八位清零
		MOV DL, BH 										;将BH复制给DL
		MOV AX, 0										;将AX清零
		MOV AL, 16
		MUL BL 											;BL(即Y)乘以16
		ADD AX, DX               						;相加得到XY坐标对应的位置
		MOV BX, AX
		MOV [DI+BX], BYTE PTR '*'						;将此位置上的值变为雷（*）
		INC CH
		POP DX 											;还原DX
		DEC DX
		JNZ GETP1

		POP DI
		POP SI
		POP DX
		POP CX
		POP BX
		POP AX
		RET
LAYM 	ENDP

;
;此子程序为判断BH=X,BL=Y的位置上是否存在雷,有雷AX=0,没有雷AX=1
;
;做上角为坐标原点,水平向右为X正方向,水平向左为Y正方向
;其中X坐标存于BH,Y坐标存于BL
;由于随机数产生的为0~15,所以XY坐标对应的位置为:[MINE]+Y*16+X 即:[MINE]+BL*16+BH
;
HAVEM	PROC NEAR
		PUSH DX
		PUSH CX
		PUSH BX
		PUSH SI
		LEA SI, MINE 									;将MINE的偏移地址给SI

		MOV DH, 0										;将DX高八位清零
		MOV DL, BH 										;将BH复制给DL
		MOV AX, 0										;将AX清零
		MOV AL, 16
		MUL BL 											;BL(即Y)乘以16
		ADD AX, DX               						;相加得到XY坐标对应的位置
		MOV BX, AX
		MOV AX, 0										;将AX清零
		CMP [SI+BX], BYTE PTR '*'						;与雷(*)做比较
		JZ HAVED										;相等则表示有雷,直接退出	
		MOV AX, 1
HAVED:
		POP SI
		POP BX
		POP CX
		POP DX
		RET
HAVEM 	ENDP

;
;此子程序为给非雷区赋值
;
;CH中从高到低的八位依次代表为(1:结点存在,0:结点不存在)：
;上、右上、右、右下、下、左下、左、坐上
;
LAYN	PROC NEAR
		PUSH DX
		PUSH CX
		PUSH BX
		PUSH AX
		PUSH DI
		MOV BX, 0 									    ;BX来统计结点数
		LEA DI, MINE 									;将MINE的偏移地址给SI
LOOPN1:
		MOV CX, 0 										;CX清零
		CMP [DI+BX], BYTE PTR '*'						;如果DX处的结点为地雷
		JZ NEXTN_1 										;取下一个结点
		MOV AX, BX

		MOV	CL, 16										
		DIV CL 											;AX除以16,余数放在AH,商放在AL,其中AH代表列(0~15),AL代表行(0~15)
		INC AL
		INC AH 											;都加一,使其变为1~16
		MOV DX, AX 										;将结果保存在DX中
		MOV CX, 0 										;CX清零

SP_UN:													;查看上结点
		CMP DL, 1 										;如果行数为第一行,则无上结点
		JZ SP_RUN 										;则跳转到右上结点
		CMP BYTE PTR [DI+BX-16], '*' 					;上结点与'*'做比较
		JNZ SP_RUN 										;不为'*'跳转到右上结点
		INC CL 											;是雷则CL加一
		
SP_RUN:													;查看右上结点
		CMP DL, 1 										;如果行数为第一行,则无上结点
		JZ SP_RN 										;则跳转到右结点
		CMP DH, 16 										;如果列数为最后一列,则无右结点
		JZ SP_RN 										;则跳转到右结点
		CMP BYTE PTR [DI+BX-15], '*' 					;右上结点与'*'做比较
		JNZ SP_RN										;不为0跳转到右结点
		INC CL 											;是雷则CL加一

SP_RN:													;查看右结点
		CMP DH, 16 										;如果列数为最后一列,则无右结点
		JZ SP_RDN 										;则跳转到右下结点
		CMP BYTE PTR [DI+BX+1], '*' 					;右结点与'*'做比较
		JNZ SP_RDN										;不为0跳转到右下结点
		INC CL 											;是雷则CL加一

SP_RDN:													;查看右下结点
		CMP DL, 16 										;如果行数为最后一行,则无下结点
		JZ SP_DN 										;则跳转到下结点
		CMP DH, 16 										;如果列数为最后一列,则无右结点
		JZ SP_DN 										;则跳转到下结点
		CMP BYTE PTR [DI+BX+17], '*' 					;右上结点与'*'做比较
		JNZ SP_DN										;不为0跳转到右结点
		INC CL 											;是雷则CL加一

SP_DN:													;查看下结点
		CMP DL, 16 										;如果行数为最后一行,则无下结点
		JZ SP_LDN 										;则跳转到左下结点
		CMP BYTE PTR [DI+BX+16], '*' 					;右上结点与'*'做比较
		JNZ SP_LDN										;不为0跳转到左下结点
		INC CL 											;是雷则CL加一

SP_LDN:													;查看左下结点
		CMP DL, 16 										;如果行数为最后一行,则无下结点
		JZ SP_LN 										;则跳转到左结点
		CMP DH, 1 										;如果列数为第一列,则无左结点
		JZ SP_LN 										;则跳转到左结点
		CMP BYTE PTR [DI+BX+15], '*' 					;右上结点与'*'做比较
		JNZ SP_LN										;不为0跳转到左结点
		INC CL 											;是雷则CL加一

SP_LN:													;查看左结点
		CMP DH, 1 										;如果列数为第一列,则无左结点
		JZ SP_LUN										;则跳转到左上结点
		CMP BYTE PTR [DI+BX-1], '*' 					;右上结点与'*'做比较
		JNZ SP_LUN										;不为0跳转到左上结点
		INC CL 											;是雷则CL加一
		JMP SP_LUN

NEXTN_1:                                                ;作为临时跳转
		JMP NEXTN

SP_LUN:													;查看左上结点
		CMP DL, 1 										;如果行数为第一行,则无上结点
		JZ NUMN 										;则跳转到NUMN
		CMP DH, 1 										;如果列数为第一列,则无左结点
		JZ NUMN											;则跳转到NUMN
		CMP BYTE PTR [DI+BX-17], '*' 					;左上结点与'*'做比较
		JNZ NUMN										;不为0跳转到NUMN
		INC CL 											;是雷则CL加一
		JMP NUMN

LOOPN_1: 												;作为临时跳转
		JMP LOOPN1

NUMN:
		MOV CH, 0 	 									;将CX高八位清零
		CMP CL, 0
		JZ ZERO
		CMP CL, 1
		JZ ONE
		CMP CL, 2
		JZ TWO
		CMP CL, 3
		JZ TREE
		CMP CL, 4
		JZ FOUR
		CMP CL, 5
		JZ FIVE
		CMP CL, 6
		JZ SIX
		CMP CL, 7
		JZ SEVEN
		CMP CL, 8
		JZ EIGHT
ZERO:
		MOV [DI+BX], BYTE PTR '0'
		JMP NEXTN
ONE:
		MOV [DI+BX], BYTE PTR '1'
		JMP NEXTN
TWO:
		MOV [DI+BX], BYTE PTR '2'
		JMP NEXTN
TREE:
		MOV [DI+BX], BYTE PTR '3'
		JMP NEXTN
FOUR:
		MOV [DI+BX], BYTE PTR '4'
		JMP NEXTN
FIVE:
		MOV [DI+BX], BYTE PTR '5'
		JMP NEXTN
SIX:
		MOV [DI+BX], BYTE PTR '6'
		JMP NEXTN
SEVEN:
		MOV [DI+BX], BYTE PTR '7'
		JMP NEXTN
EIGHT:
		MOV [DI+BX], BYTE PTR '8'
		JMP NEXTN	

NEXTN:
		INC BX 											;BX加一,取下一个结点
		CMP BX, 256 									;BX等于256则结束
		JNZ LOOPN_1 									;不等于256继续循环

		POP DI
		POP AX
		POP BX
		POP CX
		POP DX
		RET
LAYN 	ENDP

;
;此子程序为获取种子程序,其中用到了随机数生成器
;产生80个种子数的随机数,存储在SEED80中
;
SEED   	PROC                         
       	PUSH CX
      	PUSH DX
     	PUSH AX
     	PUSH BX
     	PUSH SI
     	PUSH DI

     	LEA SI, SEED10
LOP0: 
        STI
        MOV AH, 0                				    	;读时钟计数器值
        INT 1AH
        MOV AX, DX            							;第一步:得到第一号一个种子DX,将DX复制给AX
        MOV CH, 0										;CH用来防止多次循环无解
LOP1:   
		MOV CL, 4
		INC CH
		CMP CH, 5
        JZ LOP0
        ROR AX, CL 										;第二步:将AX循环右移4位,得到二号种子两个AH和AL									
        CMP AH, AL
        JZ LOP1											;确保AH与AL不等
        MOV [SI], AH 									;将AH放入SEED10中
        MOV [SI+1], AL 									;将AL放入SEED10中

LOP2:
		MUL AH 											;循环超过4个或者第一次,AH与AL相乘
		MOV CH, 0										;CH清零
         										
LOP3:   
		MOV CL, 4
		INC CH
		CMP CH, 5
        JZ LOP2
        ROR AX, CL 										;第三步:AH与AL相乘之后，再将AX循环右移4位,得到新的AH和AL
        CMP AH, AL 										;确保AH、AL、[SI]、[SI+1]四个数不等
        JZ LOP3											
        CMP AH, [SI]
        JZ LOP3
        CMP AH, [SI+1]
        JZ LOP3
        CMP AL, [SI]
        JZ LOP3
        CMP AL, [SI+1]
        JZ LOP3
        MOV [SI+2], AH 									;将AH放入SEED10中
        MOV [SI+3], AL 									;将AL放入SEED10中,第二步完成,得到三号种子SEED10中的4个

        MOV AX, [SI]									;三号种子相互异或,得到四号种子SEED10中的10个
        XOR AX, [SI+1]
        MOV [SI+4], AX
        MOV AX, [SI]
        XOR AX, [SI+2]
        MOV [SI+5], AX
        MOV AX, [SI]
        XOR AX, [SI+3]
        MOV [SI+6], AX
        MOV AX, [SI+1]
        XOR AX, [SI+2]
        MOV [SI+7], AX
        MOV AX, [SI+1]
        XOR AX, [SI+3]
        MOV [SI+8], AX
        MOV AX, [SI+2]
        XOR AX, [SI+3]
        MOV [SI+9], AX                                  
        												
		LEA DI, SEED80									;第四步:三号种子的10个种子分别循环右移一位8次，得到四号种子SEED80中的80个
        MOV CH, 0
        MOV BH, 0
LOP10:													;此时套用两层循环,第一层循环(外层)为循环三号种子中的10个种子
		MOV BL, CH    									;CH为第一层循环(外层)计数(10),代表10个种子
		MOV CL, 0										;CL为第二层循环(内层)计数(8)
		MOV AX, [SI+BX]									;每个第二层循环处理的种子为[SI+CH],暂存至AX做处理
LOP11:													;第二层循环(内层)为三号种子中每个种子做循环右移一位处理8次
		PUSH AX                        					;将AX暂存至DX
		MOV AL, CL                                      ;此处开始计算四号种子中种子的存放位置,存放位置公式为[DI+CH+CL*10]
		MOV DL, 10
		MUL DL
		MOV BL, CH
		ADD BX, AX
		POP AX 		                                    ;还原AX
		MOV [DI+BX], AX 								;计算种子存放位置结束
		PUSH CX
		MOV CL, 3
		ROR AX, CL
		POP CX
		INC CL
		CMP CL, 8
		JNZ LOP11
		INC CH
		CMP CH, 10
		JNZ LOP10

		POP DI
		POP SI
		POP BX
	    POP AX
        POP DX
        POP CX
        RET
SEED    ENDP

;
;此子程序为获取当前时间,输出从今天凌晨到现在过的分钟数
;CX:DX组成一个32位的计数器，cx代表高位，dx代表低位。
;系统时钟正常时，在每天0点时CX:DX=0，然后该计数器以每秒约18.2的步长计数。。。。
;到0点时CX:DX又复位为0。周而复始。。。
;
GET_T 	PROC 	NEAR
       	PUSH CX
      	PUSH DX
     	PUSH AX
     	PUSH BX
     	PUSH SI
     	PUSH DI
     	LEA DI, STA_T

     	MOV AH, 0  
		INT 1AH

		MOV BX, DX   									;暂存DX
		MOV AX, DX 										;将低16位放置AX中
		MOV DX, CX 										;将高16位放置DX中
		MOV CX, 1092								
		DIV CX 											;除以（18*60）得到现在为止过去的分钟数
		MOV WORD PTR [DI], AX 							;保存起来

		POP DI
		POP SI
		POP BX
	    POP AX
        POP DX
        POP CX
        RET
GET_T   ENDP

;
;此子程序为计算还剩下的游戏时间,输出在BL中
;
REM_T 	PROC 	NEAR
       	PUSH CX
      	PUSH DX
     	PUSH AX
     	PUSH SI
     	PUSH DI
     	LEA SI, STA_T

     	MOV AH, 0  
		INT 1AH

		MOV BX, DX   									;暂存DX
		MOV AX, DX 										;将低16位放置AX中
		MOV DX, CX 										;将高16位放置DX中
		MOV CX, 1092 										
		DIV CX 											;除以（18*60）得到现在为止过去的分钟数

		MOV BX, WORD PTR [SI]							;获取游戏开始的时间
		SUB AX, BX  									;现在的时间减去游戏开始的时间,得到已经过去

		CMP AX, 001EH 									;30的十六进制为1EH,与30比较
		JGE TIME_OUT1 									;如果大于等于,则时间超时

		MOV BX, 001EH                                  
		SUB BX, AX                                      ;30减去已经过去的时间,得到剩下的时间

		CMP BX, 001EH 									;与30相比,30的十六进制为1EH
		JZ TRIRTY
		CMP BX, 0014H 									;与20相比,20的十六进制为14H
		JGE TWENTY
		CMP BX, 000AH 									;与10相比,10的十六进制为0AH
		JGE TEN 										
_ONE:													;剩下几分钟									
		ADD BX, 3030H 	  								;0的ASCLL码的16进制为30H
		JMP END_T

TRIRTY: 												;剩下30分钟
		MOV AX, 001EH
		SUB BX, AX 										;得到剩下的时间的尾数
		ADD BX, 3330H 	  								;3的ASCLL码的16进制为33H,0的ASCLL码的16进制为30H
		JMP END_T

TWENTY: 												;剩下20多分钟
		MOV AX, 0014H
		SUB BX, AX 										;得到剩下的时间的尾数
		ADD BX, 3230H 	  								;2的ASCLL码的16进制为32H,0的ASCLL码的16进制为30H
		JMP END_T

TEN: 													;剩下10多分钟
		MOV AX, 000AH
		SUB BX, AX 										
		ADD BX, 3130H 	  								;1的ASCLL码的16进制为31H,0的ASCLL码的16进制为30H
		JMP END_T

TIME_OUT1:
		MOV BX, 3030H

END_T:
		POP DI
		POP SI
	    POP AX
        POP DX
        POP CX
        RET
REM_T   ENDP


DO2:
	JMP GAME1
GEND0:
    MOV AH,4CH										;退出游戏
	INT 21H
;=========/*单机*/========
GAME1:	                               
	MOV AL,2									;在屏幕上显示输入的内容
	MOV AH,0
	INT 10H										;设置80*25黑白方式，清空屏幕
	CALL INITIAL									;初始化计数器
	CALL PRINT									;打印棋盘
HERE1:
	MOV DX,OFFSET PUT								;放置棋子
	MOV AH,09H									;在屏幕上显示输入的内容
	INT 21H
	MOV AH,1									;若输入的是ESC则退出
	INT 21H
	CMP AL,27									;若输入的是ESC
	JE QUIT										;退出游戏
	JMP RXY1									;否则输入坐标X Y
QUIT:											;退出游戏的信息
	MOV STATE,2									;把STATE的值设为2
	MOV DX,OFFSET EXIT								;有人退出就显示退出消息
	MOV AH,09H									;使用21H号中断的显示输入功能
	INT 21H 
	JMP GEND1									;游戏结束
RXY1:											;记录坐标X Y(ASCII码)
	MOV X,AL									;记录x的坐标
	INT 21H										;显示在屏幕上x的值
	CMP AL,27									;若是ESC则退出
	JE QUIT										;退出记录坐标x
	INT 21H										;显示在屏幕上y的值
	CMP AL,27									;若是ESC则退出
	JE QUIT										;退出记录坐标y
	MOV Y,AL									;记录y的坐标
N1:	MOV AH,07									;无回显输入
	INT 21H
	CMP AL,27									;若是ESC则退出
	JE QUIT										;退出游戏
	CMP AL,13									;若是回车则继续，否则等待回车
	JNE N1										;继续执行N1程序
	MOV AH,2
	MOV DL,0AH									;显示光标的行坐标
	INT 21H										;输出回车换行
	MOV DL,0DH									;显示光标的列坐标
	INT 21H										;输出回车换行
	MOV FLAG,1									;flag的值为1
	CALL CHECK									;检查可否落子，将X，Y改变为真实的数值
	CMP FLAG,1									;可以落子
	JE THERE1									;可以落子则判断落子
	JMP HERE1									;如果不可以落子则重新输入
THERE1:
	MOV MY,1									;我的坐标是1，对方的坐标是2
	CALL PUTDOWN1									;落子v
	CALL ISWIN									;判断输赢，有结果则OVER=1
	CALL PRINT									;打印棋盘
	CMP OVER,1									;游戏结束																		
	JNZ HERE1
	MOV DX,OFFSET GAMEEND								;游戏结束的信息提示
    MOV AH,09H										;在屏幕上显示输入的内容
    INT 21H
    MOV AH,02H										;使用10H中断的设置位置功能																							
    MOV DL,00H										;设置光标的行坐标
    MOV DH,11H										;设置光标的列坐标
    INT 10H
    MOV STATE,3										;游戏结束我退出
GEND1:
	MOV AH,4CH									;退出游戏
	INT 21H
;=========/*初始化子程序*/========
INITIAL PROC NEAR										;计数器信息的提示
    MOV AX, CS
    MOV DS, AX
    MOV AX, 2573H                       								; AH=25H置中断向量
    INT 21H
    CLI
    MOV DX, 0D84CH                      								; PCI9052 中断状态、控制寄存器地址低位
    MOV AL, 43H                         								; 最低为1，开中断
    OUT DX, AL
    INC DX                              									; PCI9052 中断状态、控制寄存器地址高位
    MOV AL, 1DH                        					 			; 清除可能的中断状态
    OUT DX, AL        
    IN AL, 0A1H                         								; 从片                                                    
    AND AL, 11110111B                   								; 开放IRQ11中断
    OUT 0A1H,AL
    IN AL, 21H                          									;总片
    AND AL, 11111011B 
    OUT 21H, AL
    STI       
	MOV AL,00010110B	                						;初始化8253通道0，工作方式3，二进制
	MOV DX,0D403H
	OUT DX,AL
	MOV DX,0D400H
	MOV AL,52			               						;计数初值52
	OUT DX,AL			           
	MOV AX,DATA
	MOV DS,AX
	MOV DX,0D409H									;8251A控制口地址
	MOV AL,0
	OUT DX,AL
	OUT DX,AL
	OUT DX,AL
	MOV AL,40H									;写操作命令字，内部复位
	OUT DX,AL
	MOV AL,4EH									;方式字：异步，1位停止位，8位数据位，无奇偶校验，波特率16
	OUT DX,AL
	MOV AL,27H									;命令字：请求发送，运行发送和接收，数据终端准备好，发间断字符
	OUT DX,AL							
	RET										;子程序结束返回
INITIAL ENDP
;=========/*检验落子位置是否合法*/========
CHECK PROC NEAR										;落子位置是否合法的检查信息 
	PUSH AX										;保存CPU现场
	PUSH BX
	PUSH CX
	PUSH DX
    CMP X,'a'										;输出大于a，合法
	JL CMPDX									;则进行数字判断
	CMP X,'f'                           								;若输出大于f，不合法
	JG ERR										;报错信息
	SUB X,39 
	JMP CMPDY
CMPDX:											;X的数字判断
	CMP X,'1'                           								;输入小于1，不合法
	JL ERR										;报错信息
	CMP X,'9'										;输入小于9，不合法
	JG ERR										;报错信息
CMPDY:                                  									;输入X合法，比较Y
    CMP Y,'A'										;输入小于A，合法
	JL CMPDY1									;则进行数字判断 
	CMP Y,'F'										;输入大于F，不合法
	JG ERR 										;报错信息
	SUB Y,7
	JMP SUBXY
CMPDY1:											;Y的数字判断
    CMP Y,'1'										;输入小于1，不合法
	JL ERR										;不合法
	CMP Y,'9'										;输入小于9，不合法
	JG ERR										;不合法
SUBXY:
    SUB X,'1'                            									;将X改变为真实的值
	SUB Y,'1'										;将Y改变为真实的值
	MOV CX,0									;传送指令
	MOV CL,X
	MOV BX,0									;清空寄存器
MULX1: 
    ADD BL,15										;棋子右移15单位
    LOOP MULX1										;循环MULX1
	ADD BL,Y										;棋子右移输入Y的值
	CMP CHESSBOARD[BX],1                 							;若此处已有棋子，输入不合法
	JE ERR							;
	CMP CHESSBOARD[BX],2								;若此处没有棋子，输入合法
	JNE RETURNC 
ERR:
    MOV FLAG,0                           								;对于不合法的输入，显示错误信息
	MOV DX,OFFSET ERROR2
	MOV AH,09H									;在屏幕上显示输入错误的信息
    INT 21H
RETURNC:
    POP DX										;恢复CPU现场
    POP CX
    POP BX
    POP AX
	RET										;子程序结束返回
CHECK ENDP
;=========/*单机落子子程序*/========
PUTDOWN1 PROC NEAR									;单机落子的信息提示					
	PUSH AX										;保存CPU现场
	PUSH BX
	PUSH CX
	PUSH DX
	MOV CX,0									;字符指针初始化
	MOV CL,X
	MOV BX,0									;清空寄存器
MULX2: 
	ADD BL,15									;字符指针右移15个字节
	LOOP MULX2									;循环MULX2
	ADD BL,Y										;字符指针右移Y个字节
	CMP TEMP,1                         	 							;根据TEMP值，轮流放置黑子和白子
	JE MM1
	MOV CHESSBOARD[BX],2								;此处没有棋子
	MOV TEMP,1									;根据TEMP值，轮流放置黑子和白子
	JMP YY1
MM1:	
    MOV CHESSBOARD[BX],1									;此处已有棋子
    MOV TEMP,0										;根据TEMP值，轮流放置黑子和白子
YY1:	
    POP DX										;恢复CPU现场	
	POP CX
	POP BX
	POP AX
	RET										;子程序结束返回
PUTDOWN1 ENDP
;=========/*判断是否获胜*/========
ISWIN PROC NEAR										;我获胜的信息提示
    MOV X,0										;初始化X和Y
    MOV Y,0
LOOPY:
    MOV CX,0										;字符指针初始化
	MOV CL,X
	MOV BX,0									;清空寄存器
MULX3: 
    ADD BL,15										;字符指针右移15个字节
	LOOP MULX3									;循环MULX3
	ADD BL,Y                           								;BX=15*X+Y
	MOV DL,CHESSBOARD[BX]               																	
	CMP ORDER,2                         								;根据执黑或执白判断自己是否获胜
	JZ L4
	CMP DL,1										;判断黑子是否可以落子
	JE PANDUAN									;判断黑子是否可以连成5个
	JMP NEXT									;进入下一轮判断
L4:
	CMP DL,2										;判断白子是否可以落子
    JE PANDUAN										;判断白子是否连成5个
	JMP NEXT 									;进入下一轮判断
PANDUAN: 										;游戏胜利的判断
    CALL TEST1                          								;横着
	CMP OVER,1									;横着连成5个游戏结束
	JE RETURNISWIN									;返回胜利的判断
	CALL TEST2                         								;竖着
    CMP OVER,1										;竖着连成5个游戏结束
	JE RETURNISWIN									;返回胜利的判断
	CALL TEST3                          								;斜上
	CMP OVER,1									;斜上连成5个游戏结束
	JE RETURNISWIN									;返回胜利的判断
	CALL TEST4                          								;斜下
    CMP OVER,1										;斜下连成5个游戏结束
	JE RETURNISWIN									;返回胜利的判断
NEXT: 
    INC Y											;Y的字符指针右移
	CMP Y,15										;比较Y的值
	JNE LOOPY
	MOV Y,0										;初始化Y的值
	INC X										;X的字符指针右移
	CMP X,15										;比较X的值
	JNE LOOPY
RETURNISWIN:
    RET											;子程序结束返回
ISWIN ENDP
;=========/*判断横向是否连成5个*/========
TEST1 PROC NEAR										;横向判断子程序
    PUSH BX										;保存cpu现场
    CMP Y,10	 									;判断横向是否有10个字节
    JG RETURN1										;若小于则横向不能连成5个
    CMP DL,CHESSBOARD[BX+1]								;判断棋盘横向是否有2个棋子连在一起
    JNE RETURN1
    CMP DL,CHESSBOARD[BX+2]								;判断棋盘横向是否有3个棋子连在一起
    JNE RETURN1 
    CMP DL,CHESSBOARD[BX+3]								;判断棋盘横向是否有4个棋子连在一起
    JNE RETURN1
    CMP DL,CHESSBOARD[BX+4]								;判断棋盘横向是否有5个棋子连在一起
    JNE RETURN1
    MOV OVER,1										;游戏结束
RETURN1: 
    POP BX										;恢复cpu现场
    RET											;子程序结束返回
TEST1 ENDP
;=========/*判断纵向是否连成5个*/========
TEST2 PROC NEAR										;纵向判断子程序
   PUSH BX										;保存cpu现场
   CMP X,10										;判断纵向是否有10个字节
   JG RETURN2										;若小于则纵向不能连成5个
   CMP DL,CHESSBOARD[BX+15]								;判断棋盘纵向是否有2个棋子连在一起
   JNE RETURN2
   CMP DL,CHESSBOARD[BX+30]								;判断棋盘纵向是否有3个棋子连在一起
   JNE RETURN2
   CMP DL,CHESSBOARD[BX+45]								;判断棋盘纵向是否有4个棋子连在一起
   JNE RETURN2
   CMP DL,CHESSBOARD[BX+60]								;判断棋盘纵向是否有5个棋子连在一起
   JNE RETURN2
   MOV OVER,1   										;游戏结束
RETURN2: 
   POP BX
   RET											;子程序结束返回
TEST2 ENDP
;=========/*判断斜上是否连成5个*/========
TEST3 PROC NEAR										;斜上判断子程序
   PUSH BX										;保存cpu现场
   CMP X,4		      								;判断纵向是否有4个字节                  																	
   JL RETURN3										;若小于则斜上不能连成5个
   CMP Y,10										;判断横向是否有10个字节
   JG RETURN3
   CMP DL,CHESSBOARD[BX-14]								;判断棋盘斜上是否有2个棋子连在一起
   JNE RETURN3
   CMP DL,CHESSBOARD[BX-28]								;判断棋盘斜上是否有3个棋子连在一起
   JNE RETURN3
   CMP DL,CHESSBOARD[BX-42]								;判断棋盘斜上是否有4个棋子连在一起
   JNE RETURN3
   CMP DL,CHESSBOARD[BX-56]								;判断棋盘斜上是否有5个棋子连在一起
   JNE RETURN3
   MOV OVER,1   										;游戏结束
RETURN3: 
   POP BX
   RET											;子程序结束返回
TEST3 ENDP
;=========/*判断斜下是否连成5个*/========
TEST4 PROC NEAR										;斜下判断子程序
   PUSH BX										;保存cpu现场
   CMP X,10										;判断纵向是否有10个字节
   JG RETURN4										;若小于则斜下不能连成5个
   CMP Y,10										;判断横向是否有10个字节
   JG RETURN4         									;若小于则斜下不能连成5个  ;不能斜下
   CMP DL,CHESSBOARD[BX+16]								;判断棋盘斜下是否有2个棋子连在一起 
   JNE RETURN4
   CMP DL,CHESSBOARD[BX+32]								;判断棋盘斜下是否有3个棋子连在一起
   JNE RETURN4
   CMP DL,CHESSBOARD[BX+48]								;判断棋盘斜下是否有4个棋子连在一起
   JNE RETURN4
   CMP DL,CHESSBOARD[BX+64]								;判断棋盘斜下是否有5个棋子连在一起
	JNE RETURN4
	MOV OVER,1   									;游戏结束																		
RETURN4: 
   POP BX
   RET											;子程序结束返回
TEST4 ENDP 	 
;=========/*打印棋盘*/========
PRINT PROC NEAR										;打印棋盘
	PUSH SI
	PUSH AX										;保存CPU现场
	PUSH DX
	MOV AH,02H									;使用10H中断的设置光标位置功能
	MOV DL,00H									;光标从0,0开始
    MOV DH,00H										;光标的列坐标
    INT 10H	
    MOV DX,OFFSET TI									;指定字符串  
    MOV AH,09H										;屏幕显示字符串
    INT 21H
	MOV X,0										;初始化X Y SI
	MOV Y,0
	MOV SI,0
LOOP2: 
    CMP Y,0										;判断Y是否为0
    JNE NOTHEAD
    MOV DL,X
    ADD DL,31H										;X的字符指针右移
	CMP DL,'9'									;判断X是否大于等于9
	JLE PP
	ADD DL,39									;X的字符指针右移39个字节 
PP:
    MOV AH,02H
    INT 21H										;使用21H中断的输出字符功能
NOTHEAD:
    MOV DL,CHESSBOARD[SI]
    MOV AH,02H
	INT 21H
	INC SI										;SI、Y指针同时右移1个字节，指向下一个字符
	INC Y										;SI、Y指针同时右移1个字节，指向下一个字符
	CMP Y,15										;判断Y的大小
	JE NEXTLINE
	MOV DL,'-'									;输出一个'-'
	MOV AH,02H									;使用21H中断的输出字符功能
	INT 21H
	JMP LOOP2									;回到循环2
NEXTLINE:
    MOV DL,32
    MOV AH,02H
	INT 21H
	MOV DL,0AH									;输出一个回车符（0AH）
	MOV AH,02H									;使用21H中断的输出字符功能
	INT 21H
	MOV DL,0DH									;输出一个换行符（0AD）
	MOV AH,02H									;使用21H中断的输出字符功能
	INT 21H
    INC X											;X的字符指针右移1个字节
	MOV Y,0										;初始化Y
    CMP X,15
	JNE LOOP2
    MOV DX,OFFSET CLEAN									;更新屏幕的信息提示
    MOV AH,09H										;使用21H中断的显示字符串功能
    INT 21H
    MOV AH,02H										;使用10H中断的设置光标位置功能
	MOV DL,00H									;光标从0,17开始
    MOV DH,10H										;设置光标的列坐标
	INT 10H
	POP DX										;恢复CPU现场
	POP AX
	POP SI
	RET										;子程序结束返回
PRINT ENDP 


CODE   ENDS
       END    START

