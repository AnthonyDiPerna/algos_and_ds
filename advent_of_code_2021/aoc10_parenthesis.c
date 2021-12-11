#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE (6)

#define TERMINATOR  ('\0')
#define NEWLINE     ('\n')
#define INVALID_VAL ('%')
#define ARRAY_LEN   (10001) //String length 10^4 (Just making it big to be safe)

#define VALID_LINE   (0)
#define INVALID_LINE (-1)
#define CORRUPT_LINE (-2)

//Assuming
//String won't be empty
//Only parens - no other chars

char parens[ARRAY_LEN] = {' '};
int indeX = 0; //had to use indeX as name ... clashed with solution.c

typedef struct 
{
    int lineLen;
    int errorCode;
} lineInfo;

bool isEmpty(void)
{
    //printf("\nisempty %c", indeX);
    return indeX == 0;
}

//true data could be pushed
//false fata could not be pushed
bool push(char val)
{
    if (indeX < ARRAY_LEN)
    {
        //printf("\npush %c", val);
        //printf("\ni %d", indeX);
        parens[indeX++] = val;
        return true;
    }
    else
    {
        return false;
    }
    
}

char peek(void)
{
    if (indeX > 0)
    {
        //printf("\npeek %c", parens[indeX-1]);
        //printf("\ni %d", indeX);
        return parens[indeX-1];
    }
    else
    {      
        return ' ';
    }
}

char pop(void)
{
    if (indeX > 0)
    {
        char tmp = peek();
        indeX--;
        parens[indeX] = ' ';
        //printf("\npop %c", tmp);
        //printf("\ni %d", indeX);
        return tmp;
    }
    else
    {
        return ' ';
    }
}

char getOpenParenType(char closedParenType)
{
    switch(closedParenType)
    {
        case ')':       return '(';   break;
        case ']':       return '[';   break;
        case '}':       return '{';   break;
        case '>':       return '<';   break;
        default :       return INVALID_VAL;
    }
}

char getClosedParenType(char closedParenType)
{
    switch(closedParenType)
    {
        case '(':       return ')';   break;
        case '[':       return ']';   break;
        case '{':       return '}';   break;
        case '<':       return '>';   break;
        default :       return INVALID_VAL;
    }
}

bool isMatch(char closedParenType)
{
    //printf("\nMatch Close %c", closedParenType);
    //printf("\nMatch Open  %c", peek());
    return (peek() == getOpenParenType(closedParenType));
}

void calcScore(char * s)
{
    //some global state ... to clean up eek
    indeX = 0;
    memset( parens, ' ', sizeof(char)*ARRAY_LEN );
    
    int debugCount = 0;
    lineInfo info = {0,VALID_LINE};
    int i = 0;
    int score = 0;
    char firstCorruptChar = ' ';
    int lineCount = 1;
    //Loop to end of string 
    for (i = 0; s[i] != TERMINATOR; i++)
    {
        //Check if we are on the next line
        if (s[i] != NEWLINE)
        {
            //Same Line
            //go through each character, if its an OPEN bracket, push, CLOSED bracket pop   
            char c = s[i];
            if(VALID_LINE == info.errorCode)
            {
                if (c == '(' || c == '[' || c == '{' || c == '<')
                {
                    //Open bracket, push onto stack
                    push(c);
                    debugCount++;
                }
                else
                {
                    //Closed bracket, check we are closing the right type
                    if (isMatch(c))
                    {
                        //Found match, pop the open bracket and continue
                        pop();
                        debugCount++;
                    }
                    else
                    {
                        //Found the wrong closing bracket
                        info.errorCode = CORRUPT_LINE;
                        firstCorruptChar = c;
                        printf("\n   CORRUPTED - expected %c actual %c debugCount %d\n",getClosedParenType(peek()),c,debugCount);
                    }
                }
            }
        }
        else
        {
            //new line!
            //add score for corrupt, ignore invalid and good
            if (info.errorCode == CORRUPT_LINE)
            {
                int tmp = 0;
                if (firstCorruptChar == ')') tmp = 3;
                if (firstCorruptChar == ']') tmp = 57;
                if (firstCorruptChar == '}') tmp = 1197;
                if (firstCorruptChar == '>') tmp = 25137; 

                score += tmp;
                printf("\n  SUB-SCORE %d Corruptchar %c TOTAL-SCORE %d\n",tmp,firstCorruptChar,score);
            }
            else if (info.errorCode == VALID_LINE)
            {
                //Check array is empty (no hanging open braces)
                if(!isEmpty())
                {
                    info.errorCode = INVALID_LINE;
                    printf("\n   INCOMPLETE - debugCount %d\n",debugCount);
                }    
            }

            printf("\nLINE %d LEN %d TYPE %d\n",lineCount, debugCount, info.errorCode);
            lineCount++;
            
            //reset line state
            indeX = 0;
            info.errorCode = VALID_LINE;
            debugCount = 0;
            //memset( parens, ' ', sizeof(char)*ARRAY_LEN );
        }
    }

    printf("\nSCORE %d TOTAL_LINES %d \n",score,lineCount-1);
            

}

int main() 
{    
  //array of characters vs string literal  
  char testString[] = "([<{<}>])";
  
  char exampleString[] = 
  "[({(<(())[]>[[{[]{<()<>>\n"
  "[(()[<>])]({[<{<<[]>>(\n"
  "{([(<{}[<>[]}>{[]{[(<()>\n"
  "(((({<>}<{<{<>}{[]{[]{}\n"
  "[[<[([]))<([[{}[[()]]]\n"
  "[{[{({}]{}}([{[{{{}}([]\n"
  "{<[[]]>}<{[{[{[]{()[[[]\n"
  "[<(<(<(<{}))><([]([]()\n"
  "<{([([[(<>()){}]>(<<{{\n"
  "<{([{{}}[<[[[<>{}]]]>[]]\n";

  char puzzleString[] =
  "[{<(<[<<(<{[[<[]{}><()[]>]]<(([]<>)<(){}>)({[]{}}([]()))>}>{{{<(()<>)[[]()]><(<>())[[]<>]>}{({()\n"
"<<[{([[{{[[[({()()}[<>[]]){<<>[]>([]<>)}]{[{{}{}}<{}{}>]{{[]<>}{[]{}}}}][{{{(){}}<<>[]>}}]]}{\n"
"([<{([<[([({[{[]{}}{{}{}}]}{[{<>{}}{(){}}]})[{[[(){}][(){}]]{<<>[]}{{}[]}}}]])]><({{{[[{{}{}}]<{<>\n"
"{{((<([<[<[((<{}>{()()})<[{}[]]{<>{}}>)<({[]{}}([][])){{[]<>}{{}<>}}>]>]><[[[[[<<>()>(()[])](<[][]>{<>{}}\n"
"{[[<[[((<[{{<[[]{}](()[])>}{<({}[])[[]<>]>}}{[(<()()><()>)({[]()}[<>()>)]}]((<{[<>[]]{{}()}}>[{<()<>>{[]\n"
"({{((<[{{{([{[(){}][<>]}([<>()][[]()])]{<{{}<>}<{}<>>>{{()[]}{()()}}})<<[(<><>)<[]()>][((){}){[]{}}]>>}}\n"
"{<(<{[[([[(<[(<>[])]<{()}<()[]>>><{<{}[]><[]>}(<<>{}><()()>)>)]]{((({{<><>}{{}{}}}{<[]()><{}<>>})<[{(\n"
"<[{(<{<((<(<{(<>{})}<<[]>(<>{})>>){{(<()[]>[[]<>])}[{[[][]]<<>()>}{[{}()]<(){}>}]}>{(((<<>\n"
"(<[{[<((((<[[[{}{}]{{}<>}]({[][]}[(){}])][{(<>[])<[]<>>}<[(){}]>]>)))<({{[<([]<>)<()<>>>[{\n"
"{{<<[<({[{([(<[][]>{[][]})<<<>[]>([]())>])[(<<[]<>>[{}()]>{([]{})})]}](<[<(<<>[]>)>{(<[]{}>[<>[]])<<[]()>((\n"
"[[[{<{[[[([[<<<>>[{}()]}[({}[])<()<>>]]]{<<<[]{}>[<>[]]><{[]<>}{[]{}}>>{(<{}{}>{<><>})({[]()}{{}<>})}})]<<<[(\n"
"(({([<{{{{<<<({}())[()<>]>{[[]()][()[]}}>>}<({({{}<>}[[]{}])(({}{}){()()})}{[(<>{}){<>{}}]{[<>[]]({}<>)}})>}(\n"
"{(([{(([<[{(<{[]<>}<()<>>>[([]{}}(<>{})])}({[<<>[]><<>{}>]}<[<()[]>[<>{}]]{<()<>>{(){}}}>)]>([<((<{}()>\n"
"({{<{{{{{{({<{<>{}}>(<<>[]>[[][]])})]{[{{{(){}}[()<>]}<[<>][[]{}]>}{[<{}<>>{<>}]{{[]{}}(<>{})\n"
"{{(([{([{([<([[]{}]{<>[]})>{(((){})[()()]){{{}<>]<()()>}}])(({{{<>{}}{[]{}}}[((){})[<>]]}<{(()[])[\n"
"{<[((<<(([{{<{[][]}>{[()<>]{()[]}}}}]))<<((<[<[][]>[[]()]][({}){[]<>}]>))>>>>))<(<<([<<[{<<><>>[(\n"
"[([[(<([(({<([{}][<>[]]){<{}{}><{}[]>}>(<({}[])>(<()()>))}{[[{{}()}{<><>}][{()[]}<()()>]>[{<<><>>{\n"
"[{[<{(<[([[[{[{}<>]({}())}(<<>>[[]<>])]{({<>()}{()()}){{[]()>{[]()}}}]]{[[{({}()){[][]}}((<><>))][[\n"
"<{(<[<<<{{[{{<{}<>>[[]<>]}[{()<>}[()<>]]}{[{{}[]}{()}]{<[]<>>([][])}}]({[[{}]{()<>}](({}{}))}>}{<[<({}()){()\n"
"<(<[<([({[<([<[]{}>{[]<>}]{{[]{}}{{}{}}})<<{()<>}({}{})><<[]()>{()<>]>>>(([{[]()}({}())]([[]()]<{}()>))\n"
"{[<<([[<([<<(<[]<>>){<<>()>(<><>)}><<{<><>}[{}[]]>([{}()])>>])>][{({[<<[<>]{<>()}>><<[<>()]{{\n"
"<<<[<<{[<<(({<{}<>>{{}<>}}[<[]<>>({}[])]))><{{<[[]()][(){}]><{{}()}(<>)>}[((<>{})(()<>))<[(){}][[][]]>]>>>]}\n"
"(([{{[{{<<{{[({}<>)(<>{})](<(){}><{}{}))}}([{({}())<<><>>}{<(){}>}]{{[{}{}]{(){}}}<([]<>){()()}>})\n"
"({{([{{({[{<<({}[])(()[])>[{{}()}[{}{}]]><<{()<>}{{}}>>}<[((()<>)([]{}))[{()()}(()<>)]]{[{(){}}{()\n"
"<[<{<[{({(([((<>{}){()[]}){{{}{}}{[]<>}}]{{({}<>)<{}[]>}<(()<>}(()[])>}))(<{({<><>}[[]()])<[{}()](\n"
"[[{[({{<{{{{[<<>[]]({}{})]<([]{})(<>{})>}{{({}{})[{}{}]}{<<>[]><{}>}}}{<(<<>[]>{{}{}})[(()<\n"
"[([(<{{[<[{[<(<>())<[]()>>{{{}}<[][]>}][[{[][]}<{}[]>]({{}()}[[][]])]}{{{<{}{}><{}<>>}{[()[]]<()[]>}}<<{[]{}}\n"
"[[(((({<<[<<({{}()}){<()()><<>[]>}>{((<><>)({}())){<[]{}><()[]>}}><[{<{}>}({{}{}}[<>()])]{{({}{})}[<\n"
"((<<[{{[[([[<[{}()]((){})>[{()[]}<<>{}>]]([<{}()>][{{}[]}[()]])]{({[()()][[]()]}(((){}){{}{}}))[{(<>())}\n"
"{[[<{<{[{{[(<<<>[]>([]())>{(()[])[<>{}]}){<(<>())(<>{})>{<[]<>>[{}[]]}}]({<<<>[]><{}()>>([[][]])}<[<{\n"
"[(<[<{<[([[{{{<>[]}[[]{}]>({[][]}[[][]])}{[(<>[])[[]]]({()()}({}[]))}]])<[<<<{<>{}}{[][]}>((()){()<>})>>\n"
"({<[<<[{[<({<{{}{}}{<>[]}>{{()}{[]<>}}}[<[{}<>][()[]]>])((<([]())((){})><[(){}]{{}()}>)[{<[]{}>[{}{}]}[\n"
"<[[([([(<(<[[(()[])]{[[]<>]({}{})}]>)>[<[{<<<>()>({}{})><([][])<{}{}>>}<([()[]]<(){}>)[([]{})[{}<>]]>]><[{({\n"
"[<{([([(<{<<{[()[]][()}}<<{}{}>>><<{[]<>}((){})>[{[]()}]>>}[(({{<>[]}[<>()]}<({}{})[{}[]]>)<[{<>{}}([][])\n"
"[<{([((<{({{[<<>()>{[]{}}](<[]()>[{}{}])}})(<{([<>()]{[][]})[{{}()}]}<((()[])(())){([]<>)([]<>)}>>{((({}()){\n"
"((<{{{<<[[<[[{[]<>}<{}[]>]<<(){}><<>>>]<<[[][]>[[][]]>{{<><>}{[]{}}}>>{{{{<>[]}{<>{}}}[[[]<>]<{\n"
"[<<[{[<({[[{{{{}[]}[<><>]}{<<>[]>[{}[]]}}<<(()[])[<>()]>[[<>{}]]>]]}{<({<([]())(<>())>[[{}[]][<>{}]]}){([\n"
"([<{({({{<[({(<><>){(){}}}<{[]{}}{[]())>)({<(){}>[<>[]]})]<[([{}{}]<{}[]>)[[()[]]]]{[{{}<>}]<(()<>)\n"
"[([{<{<{(<<(({[]{}}({}()))){{(<>())(<><>)}(([]{})<{}[]>)}><[<[{}{}]({}{})>]{[<[]()>(<>{})]<({}()\n"
"((<{[(<<[([<{([]{}){<><>)}[[[][]]({}())]>[[{<>()}[()<>]](({}<>)([]))]][<((()[])<()[]>)[[<>()]]>])<<{[\n"
"{[[<{<<[{{(((<{}[]>(()))[<<>()>{[][]}])){<([[]{}]{{}[]})<{{}()}{()()}>}}}[{[[<(){}>{{}()}]\n"
"{[{[<<[{[{([(<[]()>(()<>))]<{[{}<>]<{}()>}<{{}{}}[()[]]>>)[{{<{}>(())}<(<>)[<>[]]>}(<{[]<>}[()()]]<{<>{}}\n"
"[{{[{{[<{[(<{[()()][<>[]]}<([][])(()<>)>>({{{}()}[()<>]}[<[]{}><[]}]))([<<<><>>({}[])>({()[]}[<>])][([(\n"
"[({<[[<{<[(<(<[][]><[]()>){[()()]{()()}}>)[<[<()>(()[])][(<><>)]>((({}())<<>[]>))]]<[{[<<>{}>[{}<>]](<{}{}>((\n"
"<{<(<((<<[[<([<><>][()[]])(<<>{}>[<>[]])>]({<<[]>(()<>)>(((){}){<>[]})}{[[[]](<>())]<<(){}><<>[]>>\n"
"[<{(<{{<(({(<<[]()>><<()<>>>)<{<{}()><()()}}(<[][]>{{}{}})>}[{[{[][]}[()<>]]{([][])(<>[])}}[{[{}()][\n"
"{{(([[[{[{({([()()]([]<>))<[{}{}](<>())>}{{{()<>}{()()}}({()[]}[{}{}])})<([([]{})<()[]>]{<<>()>})>}[[\n"
"(((<[{<[{([[{[[]<>]{<>{}}}[[{}<>](<>{})]]<<[(){}][[]{}}>{[[][]]}>][{{[[]{}]([]{})}[([])<<>>]}\n"
"<[<[[([[[[{{{([]()){(){}}}<[[]{}](<><>)>}}]]]{([[<[(()())(()[]]][[<>{}]<<>[]>]>(<[<>]<<><>>>({{}{}}([]{\n"
"({(([<<[{{[(<({}<>)<[]<>>>(<{}<>>{(){}}))]{(({{}[]})({{}<>}((){}]))[({{}()}[()<>])<({}()){<>()}>]}}}[<\n"
"<[<({[[<<([[((<>())[<><>]){[<>[]]<<>>}]]{([<{}[]>{<><>}])})<<[<([]<>)(()<>)>(<{}()>([]<>))]>[\n"
"({({{[[<<([[({()[]}[<><>]){(()<>){<><>}}][{{<>[]}(<><>)}{[[]<>]<[]>}]])>([[<(({}[])<()>)(<()>[<>{\n"
"<([{(({<[{([<[[]<>]<()<>>><(<>())({})>][[(<>[]){[]{}}]{(<>[])<()[]>}])({[{{}()}{[]()}]}{{[[]{}]({}<>)\n"
"[([{({(({{<<<<(){}>[<>[]]>([<>()][<>[]])>[{(()())[()<>]}<{[][]}[<>{}]>]>}<[<([[]()][<>()])((<><>){[]})>\n"
"<({[{{[{{[([{({}()){{}{}}}<(()())[[][]]>][<[<>()][{}[]]><<<><>>>])([[({}{})(()<>)]{<<><>>([]<>)}]{{<()[]\n"
"<{{<{(([(<<<{{[]()}[[]()]}>{{[{}<>]<()<>>}[{{}{}}[{}[]]]}>>([([<()()>[{}<>]])([<()[]>[<>()]]{([]{})}\n"
"{<({<{[{{({[<{{}()}[()()]>{({}<>)}][<<()()>{[][]}>{<<>()><{}{}>}]})}{(<{<[()()]>}<{({}){()()}}(<[]<>><\n"
"(({{({{{<[[({((){})[<>[]]}[{<>{}}[[]()]])]{<<(<>){{}()}>[<<>>{{}{}}]>([(()[])][([]())<<>()>])}][<[[\n"
"[{[[[{<<<[<{({[]()}({}{}))[{<>}{<>[]}]}>[((<<><>>[[]<>])[[[]<>]<[][]>]){[[{}()][{}<>]]({[]\n"
"<<[{({[[[<[[[<[][]>]{{[]()}(()<>)}]{[[(){}}<{}()>][{<>{}}({}{})]}](({([]{})<()()>}[({}())]))>(<{(<(){}>)}\n"
"({<([[(<(({{<{{}[]}[[]<>]>}[<(<>[])<{}{}>><[[]<>][[]{}]>]}<[({<>{}}{{}()})(<[]()>(()<>))]([<{}()\n"
"((<[{[{[{{<[{[<>{}]}[<[][]><()>]]{{<()[]>}<[(){}]{{}<>}>}>}<(([[[]{}]<[]<>>]{[{}{}]<()[]>})[[{[]{}}{{}\n"
"[([(<([<(<<{(<{}{}>{()<>})[([]())[[]]]}[{{[]<>}((){})}<{{}[]}([]())>]><{[[<>()]]<({}())[{}<>]>}{[({}<>)\n"
"[{[<([<{<{{[[{{}{}}{<><>}]<[[]()]{[]{}}>][{({}{}){[][]}}<<{}{}>([]()]>]}[<<({}<>){()<>}>({(){}}<{}{}>)><([{}\n"
"<{((<{{<{({(([<>{}]{()<>}))(<({}[])(<>())><{{}()}[<>[]]>)}]}(<{{(({}<>)[{}{}])<<<>[]>>}}((<<<\n"
"<[<({<({{([{<<<>[]><[]{}>>(<()()>({}[]))}(((()())<{}[]>))][[[<(){}>[()()]][[{}[]]]]])}([(([{[][]}(()())][{()\n"
"[({{[<((<{{{<[[][]]({}{})>{(<>[]){[]}}}([{()[]}{[]{}}])]}{[<<[(){}]<[]<>>>{({}<>)([]())}>]\n"
"{[{(<({<[[(<<({}<>){[]{}}>(({}{})(<>[]))>({[()[]]<<>{}>}<[[][]]({}())>))(([[<>[]]([]{})][<{}>>){{[[]\n"
"{<([[(<<[(<{<<<>{}><<>>>(({}[])<()<>>)}<{<[]{}><()()>}[{(){}}]>>){<<<{{}{}}{()<>}>{{()[]}{()}>><<<<>[\n"
"<{[{(<{[<<(<<([]{})(())>[({}[]){{}()}]>)(<{[[]()]}>[{(()<>)(()<>)}{[{}<>]{()()}}])>[(({<<>[]>({}[]}}{([]\n"
"{{{([{[([[[{[{(){}}{[]()}][<<>()>]}([[[][]](<><>)])]]]{(<[(<<>[]>[{}<>])(({}[])({}{}))]{<([]{})<[][]>>((\n"
"({{[(<<<[({<[{[]<>}<{}<>>]<<()>[(){}]>>[<<<>{}>{{}[]}><({}{})>]})][(<{[(<>())]}(([<><>){[][]})\n"
"([[([{[<<{(<{<[]()>[(){}]}[(<><>){()<>}]>){{[<()()><<>[]>](<[][]>{[]<>})}<[{<>()}{()[]}]{{<><>}[<><>]}>}}{<<\n"
"<[<([<[(({<{{<(){}><<>[]>}{{<>{}}((){})}}<<[{}]({}[])}{<()()><()<>>}>>[[[{<><>}([][])](({}<>)((){}\n"
"<<[<[[<(<{(<{[[][]]{(){}}}<{{}()}<()[]>>><{<{}>}{{<>{}}[()<>]}>)}><{[<{(()[]]<()()>}<{(){}}\n"
"([([(<({{(<<{[[]<>]({}())}{{[][]}<()[]>}>>)}})(<{{<({<()[]>([]{})}[{{}<>}[<>()]])><[({<>()}{<>[\n"
"<(({{(<(<[{<[{{}[]}[<>{}])(<()<>>({}{}))>[<[<>[]]{{}}>[({}<>)[[]{}]]]}<[[{[]<>}{[]<>}]<(()()){<\n"
"{(<(([{([<({[[<>[]]{<>[]}]{{[]<>}{()}}})<[<[[]()][<>{}]>{[<>{}]<()<>>}]<(<[]>[[]()])([<>()](()<>))]>>])\n"
"{{[([[<<([(<{{{}[]}<()[]>}({[]{}}[[]{}])>(<{(){}}<(){}>><[[]{}]>))])>{{<<{<[()[]]<[]<>>>}{{(()\n"
"{{<[{[<([({<[{[][]}<<>()>]{{[]{}}({}())}]({{[]<>}}(<()<>>(<>[])))}([<[()()][[][]]>((<>{}){()<>})]\n"
"{[[{<{<<{((<<<<><>><[][]>>([()<>]<{}[]>)>{((<><>)({}()))([{}{}][<>])})<({({}[])({}())}<[()[]][{}<>]\n"
"<({{{(<{({<<(<[]<>>{{}})>[[({}<>)(()())]{[[]{}]({}{})>]>({<<()<>>[<>[]]>((()<>)([]{}))}[[([]<>)<[]<>>]{{{}<>}\n"
"{<[{([([{<[{<[<><>]([]())>((<>[])([][]))}]>(({[<[]>[[]<>]]{{{}[]}{[]{}}}}){(<{{}{}}([]<>)>)})}\n"
"(<[{{<([<[({<{{}{}}><{{}<>}([]{})>}<<[()()]{{}()}>[[[]()]({}{})]>)[[{<()[]><[]()>}<[<>()][(){}]>]]]<{(<<[]{}>\n"
"<{([[<{<([({{[<>{}]({}[])](<[][]>{{}[]})}{{{<>[]}<{}()>}<[{}[]]{{}()}>})([<[[][]]{<>()}>[<<>()>({\n"
"<{[{(<<{[<(<{{()<>}{[]()}}[([][])<{}[]>]>[[[{}<>}[()[]]][({}[]){()<>}]]){[<[{}[]][[][]]>(<{}>([][]))][[\n"
"{[{<([<<({<<(<<><>><{}[]>)[(<>()){[]{}}]>(<{{}<>}[[]<>]>([{}{}]))>}([{<(()[])[()<>]>{{()()}}}[[<[][\n"
"<{(<[{<<[[[({([]{})([]<>)}{([][])([][])})[[<[]{}><<><>>]<[{}<>]({}[])>]]<{[[{}{}]({}[])]<{[]<>}(()<>)>}[({<\n"
"(<[{([[[{[<([<{}[]>][(<>[])(()<>)])<[{[][]}([]())]>>][{([(<>())[()[]]])}({({()[]}[{}{}])}{[<[]<>>([]()\n"
"<({{[([[<<[(({{}}{{}()})<<()()><<><>>>)<[<{}[]><()<>>][<<>{}]([]{})]>]>>{<((<<[]>(())>{{()<>}}\n"
"[[[[<{[[({[{{[()[]]([]())}}<<{{}<>}(<>)>({{}{}}<[][]>)>]<{(<<>()>{(){}})[{()()}<<>>]}([{{}]<{}<>>][[()()](\n"
"(([[<(([{<({<<()()>>{<()<>><{}{}>}}{((<>()){()[]})<([]{}){()[]}>})>(<[[<[]()>{[][]>][[[]]<<>\n"
"{[<[({<(<<[[((<>())(<>[])){(<>[])(<>[])}][({[]{}}{{}<>})[<(){}>((){})]]]>>[<<{<<()[]>[[][]>>(\n"
"{<<(<([<<<((({[][]}{<><>})[{[][]}([]{})])<[<{}{}>({}())][((){})[[]()]]>)<[{(()<>)(()[])}](<[\n";


  //printf("\nINPUT : %s ",strlen(puzzleString));
  calcScore(puzzleString);
  
  return 0;
}