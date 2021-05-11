inoremap ' ''<ESC>i
inoremap " ""<ESC>i
inoremap ( ()<ESC>i
inoremap [ []<ESC>i

"inoremap { {<CR>}<ESC>O 大括号不要自动换行
"大括号不要自动换行
inoremap { {}<ESC>i

" 将tab键绑定为跳出括号  
"inoremap <TAB> <c-r>=SkipPair()<CR>

"打开文件类型检测, 加了这句才可以用智能补全
set completeopt=longest,menu

set shortmess=atI " 启动的时候不显示那个援助乌干达儿童的提示 
set showcmd "输出的命令显示出来

autocmd InsertLeave * se nocul " 用浅色高亮当前行
autocmd InsertEnter * se cul " 用浅色高亮当前行 

set foldenable " 允许折叠
set foldmethod=manual " 手动折叠 

set nocompatible "去掉讨厌的有关vi一致性模式,避免以前版本的一些bug和局限 

" 映射全选+复制 ctrl+a
map <C-A> ggVGY
map! <C-A> <Esc>ggVGY
map <F12> gg=G
" 选中状态下 Ctrl+c 复制
vmap <C-c> "+y
"去空行
nnoremap <F2> :g/^/s*$/d<CR> 

"代码补全
set completeopt=preview,menu 

"共享剪贴板
set clipboard+=unnamed 

" Tab键的宽度
set tabstop=4
" 统一缩进为4
set softtabstop=4
set shiftwidth=4
" 不要用空格代替制表符
set noexpandtab
" 在行和段开始处使用制表符
set smarttab

"禁止生成临时文件
set nobackup
set noswapfile
"搜索忽略大小写
"set ignorecase
"搜索逐字符高亮
set hlsearch
set incsearch

set gdefault "行内替换
set encoding=utf-8
set fileencodings=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936,utf-16,big5,euc-jp,latin1 "

"编码设置

set guifont=Menlo:h16:cANSI "设置字体
set langmenu=zn_CN.UTF-8
set helplang=cn  "语言设置

set ruler "在编辑过程中，在右下角显示光标位置的状态行

set laststatus=1  "总是显示状态行

set showcmd "在状态行显示目前所执行的命令，未完成的指令片段也会显示出来

set scrolloff=3 "光标移动到buffer的顶部和底部时保持3行的距离"""""""

set autowrite "在切换buffer时自动保存当前文件"

set showmatch
set selection=exclusive
set selectmode=mouse,key

set wildmenu  "增强模式中的命令行自动完成操作

set linespace=2 "字符间插入的像素行数目
set whichwrap=b,s,<,>,[,] "开启normal 或visual模式下的backspace键空格键，左右方向键,insert或replace模式下的左方向键，右方向键的跳行功能

filetype plugin indent on
"分为三部分命令:file on,file plugin on,file indent on 分别是自动识别文件类型, 用用文件类型脚本,使用缩进定义文件""]""

filetype on "打开文件类型检测功能

autocmd BufNewFile *.java,*.c* exec ":call SetTitle()"
func SetTitle()

    if &filetype == 'cpp'
	    call setline(1,"/************************************************************************")
		call append(line("."), "   File Name: ".expand("%:t")) 
		call append(line(".")+1, "   Author: ljl") 
		call append(line(".")+2, "   Mail: ") 
		call append(line(".")+3, "   Created Time: ".strftime("%c")) 
		call append(line(".")+4, "************************************************************************/") 
		call append(line(".")+5, "")
		call append(line(".")+6, "#include<iostream>")
		call append(line(".")+7, "#include<algorithm>")
		call append(line(".")+8, "#include<ctime>")		
        call append(line(".")+9, "using namespace std;")
		call append(line(".")+10, "#define random(x) (rand()%(x+1))")
        call append(line(".")+11, "")
		call append(line(".")+12, "int main(){")
		call append(line(".")+13, "	return 0;")
		call append(line(".")+14, "}")
    endif
    if &filetype == 'c'
	    call setline(1,"/************************************************************************")
		call append(line("."), "   File Name: ".expand("%:t")) 
		call append(line(".")+1, "   Author: ljl") 
		call append(line(".")+2, "   Mail: ") 
		call append(line(".")+3, "   Created Time: ".strftime("%c")) 
		call append(line(".")+4, "************************************************************************/") 
		call append(line(".")+5, "")
        call append(line(".")+6, "#include<stdio.h>")
		call append(line(".")+7, "#include<stdlib.h>")
		call append(line(".")+8, "#include<time.h>")		
		call append(line(".")+9, "#define random(x) (rand()%(x+1))")
        call append(line(".")+10, "")
		call append(line(".")+11, "int main(){")
		call append(line(".")+12, "	return 1;")
		call append(line(".")+13, "}")
    endif
	if &filetype == 'java'
        call append(line(".")+1, "public class ".expand("%:r").expand("{")) 
        call append(line(".")+2, "	public static void main(String[] args) {") 
        call append(line(".")+3, "	}") 
        call append(line(".")+4, "}") 
    endif
	
    "新建文件后，自动定位到文件末尾（这个功能实际没有被实现，即下面的语句无效，暂不知道原因）
    autocmd BufNewFile * normal G
endfunc

"C,C++ 按F5编译运行
map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
        exec "w"
		exec "clear"
        if &filetype == 'c'
			exec "!clear"
                exec "!g++ -I %:h % -o %"
                exec "!time ./%<"
        elseif &filetype == 'cpp'
				exec "!clear"
                exec "!g++ -std=c++17 % -o %<"
                exec "!time ./%<"
        elseif &filetype == 'java'
				exec "!clear"
                exec "!javac %"
                exec "!time java %<"
        elseif &filetype == 'sh'
				exec "!clear"
                :!time bash %
        elseif &filetype == 'python'
                exec "!clear"
                exec "!time python3 %"
		endif
endfunc

"C,C++的调试
map <C-F5> :call Rungdb()<CR>
func! Rungdb()
exec "w"
exec "!clear"
exec "!g++ % -g -o %<"
exec "!gdb ./%<"
endfunc
"
set tags=/home/lsh/files/tags
set number
let Tlist_Auto_Open = 1
let Tlist_Ctags_Cmd = '/usr/local/bin/ctags'
let Tlist_Show_One_File = 1
let Tlist_Exit_OnlyWindow = 1
""""""""""""""""""""""""