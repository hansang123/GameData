#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#define MAX_ENHANCEMENTStage1 20
#define WAIT_TIME 0.5
#define INITIAL_MONEY 2000000
#define ENHANCEMENT_THRESHOLD 10
#define REVIEW_TICKET_COST 200000
#define BOSSLEVEL 5
//수정사항 작성법 : 
// [날짜]
//    (수정내용) - (추가 업데이트 내용)
/// <summary>
/// * 수정사항 *
/// [04-14]
///     던전 개설(5개의 던전 스테이지 제작 완료) - 디자인 필요
/// 
/// </summary>
char* enhancementMessages1[] = {
    "병아리 신입생(세상의 때가 묻지 않은 귀여운 신입생이 등장했다!)",
    "C언어를 배운 1학년(김영철 교수님께 칭찬을 받은 귀여운 1학년이다.)",
    "HTML5를 배운 1학년(이윤임 교수님의 사랑을 받는 1학년이다.)",
    "포토샵을 배운 1학년(노은석 교수님께서 매우 만족하신다.)",
    "파이썬을 배운 1학년(이은석 교수님께 욕을 많이 먹었다. 슬슬 사람이 이상해진다.)",
    "JavaScript를 배운 1학년(이윤임 교수님께선 큰 신뢰를 걸고 계신다.)",
    "C언어응용을 배운 1학년(김영철 교수님께 혼났다. 분명 C언어를 배웠는데...??)",
    "유니티를 배운 2학년(이성현 교수님께서 걱정하신다. 원래 착했던 애가 이상해지고 있다...)",
    "C# 프로그래밍을 배운 2학년(윤수미 교수님께서 좋아하신다. 다행히 아직 초반이라...)",
    "앱기획을 배운 2학년(김영철 교수님께 맞기 직전까지 갔다. 한강물의 온도가 궁금하다...)",
    "현타가 온 대학생(교수님께 혼나고, 과제에 치이고... 학생의 눈앞에 눈물이 글썽인다.)",
    "반응형웹을 배운 2학년(이은석 교수님께서 좋아하신다. 잠을 자지 않고 과제를 끝냈다.)",
    "C++을 배운 2학년(이제 C계얼 언어를 다 배웠다. 근데 포인터는 도저히 이해가 안된다...)",
    "유니티로 게임을 개발한 3학년(코피를 흘려가며 게임을 만들었다. 이성현 교수님께서 \"이게 게임이 맞나\"라고 하셨다.)",
    "HTML과 CSS로 웹을 만들어 본 3학년(이윤임 교수님께 잔소리를 많이 들었다. 그래도 내심 교수님께서 기특해하신다.)",
    "전공동아리 멘토를 하는 3학년(후배들의 존경을 받고 있다. 이은석 교수님과 이성현 교수님도 그렇게 생각하실까?)",
    "3D모델링을 배운 3학년(노은석 교수님과 1대1 면담을 했다. 아트도 괜찮은 것 같은데... 어디로 갈지 모르겠다.)",
    "창업동아리를 하는 3학년(매일 학교에 21시까지 후배, 동기들과 같이 작업을 한다. 이정도면 귀신이다.)",
    "기획서 작성을 마스터한 3학년(본인은 정말 잘한다고 생각한다. 이은석 교수님과 이성현 교수님도 그렇게 생각하실까?)",
    "현장 실습을 다녀온 3학년(회사에선 오랜만에 인재가 들어왔다고 한다. 하지만 본인은 회사가 별로다.)",
    "졸업 가운을 입고 있는 대학생(모든 능력을 탑재했다. 이제 진짜 지옥을 향해 걸어간다.)"
};
// 2스테이지 
char* enhancementMessages2[] = {
"크래프톤 면접을 보고왔다.. 결과가 어떻게 나왔을까??"
"꿈에 그리던 크래프톤을 붙었다.. 희망으로 가득찬 나의 앞날이 어떻게 될까??"
"첫 출근 아침 .. 9시까지 출근이여서 8시에 집에서 출발했다.. 9시 되기 20분전.. 회사앞이다..."
"다행이도 9시 10분전에 도착하였다.. 첫 출근인데 늦을수는 없지?!"
"첫날에는 어떻게 해야하는건지 선임분이 알려주실거를 알려주시고 계시다.."
"6시에 퇴근시간에 맞춰 집을 가려고 했었는데.. 신입 회식을 한다고??"
"회식을 끝내고 집에 들어왔는데 몹시 힘이 들어 기절을 해버렸다.. 일어나니? 7시반??"
"비슷비슷한 일상을 보내다... 계약직에서 정규직으로 성공을 했다!"
"점점..회사에 녹아드는 개발자이다.. 근데 너무 힘든데??"
"스펙을 쌓을만큼 쌓은 개발자. 딴 직종으로 이직을 원하는데..."
};
int isTry = 0;                  // 강화 시도 여부 선택 변수
int level = 0;                  // 현재 무기의 강화 수치
int money = INITIAL_MONEY;      // 현재 소지금 
int choice;
bool isGameOver = false;        // 게임 종료 여부 변수
int tickets = 0;
int dungeonSelect = 0;
// 강화 성공 확률 배열
float enhancementProbabilitiesStage1[MAX_ENHANCEMENTStage1 + 1] = {
    100.0f,100.0f,100.0f,100.0f,
    100.0f,100.0f,100.0f,100.0f,
    100.0f,100.0f,100.0f,100.0f,
    100.0f,100.0f,100.0f,100.0f,
    100.0f,100.0f,100.0f,100.0f
};
// 강화 시도 비용 배열
int enhancementCosts[MAX_ENHANCEMENTStage1 + 1] = {
    20000, 30000, 40000, 50000, 60000,
    70000, 80000, 90000, 50000, 55000,
    60000, 65000, 70000, 75000, 80000,
    85000, 90000, 95000, 100000, 105000,
};
// 학생 급여 배열
int studentSalaries[MAX_ENHANCEMENTStage1 + 1] = {
    0, 50000, 60000, 65000, 70000,
    75000, 80000, 85000, 90000, 95000,
    100000, 105000, 110000, 115000, 120000,
    125000, 130000, 135000, 140000,145000,
    150000
};
int BossMobHP[BOSSLEVEL + 1] = {
    5000,100000,500000,3000000,10000000
};
int JihoPower[MAX_ENHANCEMENTStage1 + 1] = {
    0,10,50,100,150,250,
    300,400,500,600,800,
    1000,1200,1400,1500,5000,
    7000,10000,30000,65000,150000
};
// 강화 유지 비용 배열
//int maintainCosts[MAX_ENHANCEMENT + 1] = {
//    0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0,
//    5000, 6000, 7000, 8000, 9000,
//    10000, 11000, 12000, 13000, 14000,
//    15000
//};
// 학생 판매 함수
void sellStudent(int* level, int* money) {
    if (*level == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("\n 아직 이지호 학생을 강화하지 않았습니다.\n");
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("이지호 학생을 취업 시켰습니다. 이지호 학생이 큰 절을 하며 떠나갑니다.\n");
        *money += studentSalaries[*level];
        printf("현재 소지금에 %d원이 추가되었습니다.\n", studentSalaries[*level]);
        *level = 0; // 학생을 판매하면 레벨 초기화
    }
}
void GoStore() {
    printf("\n *** 상점으로 이동 ***\n\n");
    Sleep(2000);
    while (1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        printf(" * 학습 재화를 사용하여 아이템을 구매할 수 있습니다 *\n\n");
        printf(" * 1. 학생 판매 (학생 가치 : %d원)\n", studentSalaries[level]);
        printf(" * 2. 복습권 구매\n");
        printf(" * 3. 메인화면 이동\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        printf("\n * 아이템을 선택하세요 : ");
        int shopChoice;
        if (scanf_s("%d", &shopChoice) != 1) {
            printf("숫자를 입력하세요.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
            continue; // 다시 입력 받기
        }
        while (getchar() != '\n'); // 입력 버퍼 비우기

        switch (shopChoice) {
        case 1:
            if (level > 0) {
                if (money < 0) {
                    money = 0;
                }
                printf("\n 강화한 레벨: + %d\n", level);
                printf("\n 판매 금액: %d원\n\n", studentSalaries[level]);
                money += studentSalaries[level];
                enhancementCosts; //현재 강화 비용
                level = 0;
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf(" \n 학생 레벨이 0이므로 학생 판매 옵션을 사용할 수 없습니다.\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            break;
        case 2:
            if (money < REVIEW_TICKET_COST) {
                printf(" \n 재화가 부족하여 복습권을 구매할 수 없습니다.\n\n");
                break;
            }
            else {
                money -= REVIEW_TICKET_COST;
                tickets++;
                printf(" \n 복습권을 구매하였습니다.\n");
                printf("\n 보유 복습권 갯수 : %d개\n", tickets);
                printf(" \n 현재 소지금: %d원\n\n", money);
                break;
            }
        case 3:
            isTry = 0;
            return;// 상점 메뉴에서 빠져나감
        default:
            printf(" 잘못된 입력입니다.\n");
            break;
        }
    }
    if (level == MAX_ENHANCEMENTStage1) {
        printf("\n축하합니다! 20단계까지 모두 클리어하셨습니다!\n");
        printf("다음 스테이지로 진행하시겠습니까? (YES: 1 / NO: 2) : ");
        scanf_s("%d", &choice);
        if (choice == 1) {
            // 다음 스테이지로 진행
            // 여기에 다음 스테이지를 초기화하거나 전환 메시지를 표시하는 코드를 추가할 수 있습니다.
            printf("\n다음 스테이지로 이동합니다!\n");
            // 다음 스테이지로 이동하기 위한 추가 코드
            level = 21; // 다음 스테이지를 위해 레벨을 0으로 초기화
            money = INITIAL_MONEY; // 다음 스테이지를 위해 돈 초기화
            // 다음 스테이지를 위한 필요한 초기화를 추가할 수 있습니다.
        }
        else if (choice == 2) {
            // 게임 종료
            printf("\n게임을 종료합니다. 수고하셨습니다!\n");
            isGameOver = true;
        }
        else {
            printf("\n잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
    else {

    }
}
void Dungeon1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n 이상현 교수님 : 아트는 무슨 아트야... 개발도 못하는 것들이..\n");
    printf("\n");
    printf("                         ..=~                     \n");
    printf("                       *=$#$$$=,                  \n");
    printf("                      ==$###*##$;                 \n");
    printf("                     !==$$*=*$$#$:                \n");
    printf("                    -=$*==!;!==$#*                \n");
    printf("                    !=*!=::~:!=$$=,               \n");
    printf("                    $**!;-,,~:=$$=:               \n");
    printf("                    ;!::-,.,~~!===~               \n");
    printf("                    ~:~::,,:!;~;*!*               \n");
    printf("                    ,~.:!-=-=~.-;;~               \n");
    printf("                    ,..~-.:-:--~;-                \n");
    printf("                       .. ,-,,,-:,                \n");
    printf("                       ,. -~,,,-,,                \n");
    printf("                      .,.,--~--,,                 \n");
    printf("                      .,..,~~,-,-                 \n");
    printf("                      .. .--,---                  \n");
    printf("                       .. .--~~,-                 \n");
    printf("                       ,,-~;;:-*;.                \n");
    printf("                        ,~:;:,$==!                \n");
    printf("                        .,  :***=!!               \n");
    printf("                      !    ~;*****!;:             \n");
    printf("                   ;!**.. ,::!*;!!;!=;            \n");
    printf("                 :**;!; ,!!*=*!**;$=*=!           \n");
    printf("                !;=!!*;.;!;*!***===!===,          \n");
    printf("               -!**!*!!.*!!$=!;!!;*==$=!          \n");
    printf("               !!*!*!!.**!!$=!;!!=$$$=;           \n");
    printf("              ,***;;;*-*;==!!!!;!!=$$=;           \n");
    printf("              !!;;!;!:;!;;:=*!!;=*$*==**          \n");
    printf("             .=!!;!;!**:@***;;!*=!$$*==!          \n");
    printf("             !!=:;*;:***;=::*!!!*=*==#=*          \n");
    printf("            :!*!:***!**!=;*!:!**!=*$$***          \n");
    printf("            !!**!;*;!!*!~=$;=;=*=***!==!          \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf(" \n                  [ HP : %d ]\n", BossMobHP[0]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int messageDisplayed = 0;
    int numberDisplayed = 1;
    while (BossMobHP[0] > 0) {
        char input = getchar();
        if (!numberDisplayed) {
            printf("                         ..=~                     \n");
            printf("                       *=$#$$$=,                  \n");
            printf("                      ==$###*##$;                 \n");
            printf("                     !==$$*=*$$#$:                \n");
            printf("                    -=$*==!;!==$#*                \n");
            printf("                    !=*!=::~:!=$$=,               \n");
            printf("                    $**!;-,,~:=$$=:               \n");
            printf("                    ;!::-,.,~~!===~               \n");
            printf("                    ~:~::,,:!;~;*!*               \n");
            printf("                    ,~.:!-=-=~.-;;~               \n");
            printf("                    ,..~-.:-:--~;-                \n");
            printf("                       .. ,-,,,-:,                \n");
            printf("                       ,. -~,,,-,,                \n");
            printf("                      .,.,--~--,,                 \n");
            printf("                      .,..,~~,-,-                 \n");
            printf("                      .. .--,---                  \n");
            printf("                       .. .--~~,-                 \n");
            printf("                       ,,-~;;:-*;.                \n");
            printf("                        ,~:;:,$==!                \n");
            printf("                        .,  :***=!!               \n");
            printf("                      !    ~;*****!;:             \n");
            printf("                   ;!**.. ,::!*;!!;!=;            \n");
            printf("                 :**;!; ,!!*=*!**;$=*=!           \n");
            printf("                !;=!!*;.;!;*!***===!===,          \n");
            printf("               -!**!*!!.*!!$=!;!!;*==$=!          \n");
            printf("               !!*!*!!.**!!$=!;!!=$$$=;           \n");
            printf("              ,***;;;*-*;==!!!!;!!=$$=;           \n");
            printf("              !!;;!;!:;!;;:=*!!;=*$*==**          \n");
            printf("             .=!!;!;!**:@***;;!*=!$$*==!          \n");
            printf("             !!=:;*;:***;=::*!!!*=*==#=*          \n");
            printf("            :!*!:***!**!=;*!:!**!=*$$***          \n");
            printf("            !!**!;*;!!*!~=$;=;=*=***!==!          \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf(" \n                  [ HP : %d ]\n", BossMobHP[0]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf(" \n { 나가기 : 0 }\n");
            numberDisplayed = 1;
        }
        if (input == '0') {
            printf(" \n 던전을 나갑니다.\n");
            return 0;
        }
        else if (input == '\n') {
            if (messageDisplayed) {
                messageDisplayed = 0;
            }
            else {
                BossMobHP[0] -= JihoPower[level];
                numberDisplayed = 0;
            }
        }
        else {
            if (!messageDisplayed) {
                printf("\n 다시 입력해주세요.\n");
                printf("{ 나가기 : 0 }\n");
                messageDisplayed = 1;
            }
        }
    }
    printf(" 으어억...내가 지다니...\n");
    Sleep(1000);
    printf(" 던전 1 완료!\n");
    return 0;
}
void Dungeon2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n 윤소미 교수님 : 하... 잠시만요...\n");
    printf("\n");
    printf("                    .,,,,. .,,                     \n");
    printf("                   :=####*!*$$*-                   \n");
    printf("                  ###########=##!                  \n");
    printf("                -=#####@@@@##$###;                 \n");
    printf("               ~*########@########*                \n");
    printf("              ,!$#######@###$#####$:               \n");
    printf("             :!==$$####$!:~--:*$####-              \n");
    printf("            ,!**=$###$$;-,,,,-:=#####              \n");
    printf("            :*=*==$$$$!-....,,~!$####-             \n");
    printf("           .!==**====*-.....,,-:=####=             \n");
    printf("           -=$***=*==:,. ...,,--*###$=             \n");
    printf("           ~$$!*****!~......,,,-;$##$=,            \n");
    printf("           !$**!=*=!~.......,,,-~*###$~            \n");
    printf("           !=***=**;,.......,,,--;$##$-            \n");
    printf("           *=**=*$=;,.....,-~~~~~:=##$~            \n");
    printf("           ~*==*$=!:~-,,.,--------;=$*             \n");
    printf("           ~*==*$=;---,,.,---**~--~*$!.            \n");
    printf("           .;$$==**$$~-,.,-~,=!;:--!=;.            \n");
    printf("           ,*$=*;!~;~-,. .,,-,-----;=-             \n");
    printf("           .:$*;-----,.. .,,,,,,,,,~!-             \n");
    printf("             *;,,....... .,,,,,...,-:-             \n");
    printf("            ,*-............,,.....,,--,             \n");
    printf("             ........,. .,,--,,.,,,,-              \n");
    printf("             ..........:-,--,,,,,,,-               \n");
    printf("              .  ...... ..,,,,,,,-,-               \n");
    printf("              .. ...... ...,------,-               \n");
    printf("              .!  .,,--,:--~~~-,----               \n");
    printf("               ;; ..,,,..,,,--,---~-               \n");
    printf("               .=,..,...,---------:,               \n");
    printf("                ;*..,......,-----~*                \n");
    printf("                ,=.,,..  ..,,---~;                 \n");
    printf("                :# .,,..,,,,---~-;#:.              \n");
    printf("               -*@  .~-,---~-~~--:#$*;             \n");
    printf("             .~:#$  ..-~~::~~~---~##$$!,           \n");
    printf("            -;~*#;  ...,-~~------~$#$$$$:          \n");
    printf("           ~;;;$$:. ....,,-------~!######==-        \n");
    printf("          ,~:**;==$;,.....,,,--,---~!##$$##$$==,    \n");
    printf("        .-::!=!:$=#;,,...,,,,-,,---~!#$$$##$$$=$*,.\n");
    printf("    ::!:~:!=!;*$$#;,,..,,,,,,,,,--~;=$=$$#$===$=$*:\n");
    printf("   ;;!*:::!*;*$$#;,,..,,,,,,,,,,-~:!!=$$#$===$====\n");
    printf("~!;;!!*!:;**!!=$#:,,...,,,,,,,,,---::**=$$=$$$$===\n");
    printf("*!:!!=*!;;!!!**$#;,,....,,,..,,,-,-~~****==$$#$===\n");
    printf("!!;*!$*=;;!!!!!=@:,.. ..... ..,,,,,-~=*===$$$$$$==\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf(" \n                  [ HP : %d ]\n" , BossMobHP[1]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int messageDisplayed = 0;
    int numberDisplayed = 1;
    while (BossMobHP[1] > 0) {
        char input = getchar();
        if (!numberDisplayed) {
            printf("                    .,,,,. .,,                     \n");
            printf("                   :=####*!*$$*-                   \n");
            printf("                  ###########=##!                  \n");
            printf("                -=#####@@@@##$###;                 \n");
            printf("               ~*########@########*                \n");
            printf("              ,!$#######@###$#####$:               \n");
            printf("             :!==$$####$!:~--:*$####-              \n");
            printf("            ,!**=$###$$;-,,,,-:=#####              \n");
            printf("            :*=*==$$$$!-....,,~!$####-             \n");
            printf("           .!==**====*-.....,,-:=####=             \n");
            printf("           -=$***=*==:,. ...,,--*###$=             \n");
            printf("           ~$$!*****!~......,,,-;$##$=,            \n");
            printf("           !$**!=*=!~.......,,,-~*###$~            \n");
            printf("           !=***=**;,.......,,,--;$##$-            \n");
            printf("           *=**=*$=;,.....,-~~~~~:=##$~            \n");
            printf("           ~*==*$=!:~-,,.,--------;=$*             \n");
            printf("           ~*==*$=;---,,.,---**~--~*$!.            \n");
            printf("           .;$$==**$$~-,.,-~,=!;:--!=;.            \n");
            printf("           ,*$=*;!~;~-,. .,,-,-----;=-             \n");
            printf("           .:$*;-----,.. .,,,,,,,,,~!-             \n");
            printf("             *;,,....... .,,,,,...,-:-             \n");
            printf("            ,*-............,,.....,,--,             \n");
            printf("             ........,. .,,--,,.,,,,-              \n");
            printf("             ..........:-,--,,,,,,,-               \n");
            printf("              .  ...... ..,,,,,,,-,-               \n");
            printf("              .. ...... ...,------,-               \n");
            printf("              .!  .,,--,:--~~~-,----               \n");
            printf("               ;; ..,,,..,,,--,---~-               \n");
            printf("               .=,..,...,---------:,               \n");
            printf("                ;*..,......,-----~*                \n");
            printf("                ,=.,,..  ..,,---~;                 \n");
            printf("                :# .,,..,,,,---~-;#:.              \n");
            printf("               -*@  .~-,---~-~~--:#$*;             \n");
            printf("             .~:#$  ..-~~::~~~---~##$$!,           \n");
            printf("            -;~*#;  ...,-~~------~$#$$$$:          \n");
            printf("           ~;;;$$:. ....,,-------~!######==-        \n");
            printf("          ,~:**;==$;,.....,,,--,---~!##$$##$$==,    \n");
            printf("        .-::!=!:$=#;,,...,,,,-,,---~!#$$$##$$$=$*,.\n");
            printf("    ::!:~:!=!;*$$#;,,..,,,,,,,,,--~;=$=$$#$===$=$*:\n");
            printf("   ;;!*:::!*;*$$#;,,..,,,,,,,,,,-~:!!=$$#$===$====\n");
            printf("~!;;!!*!:;**!!=$#:,,...,,,,,,,,,---::**=$$=$$$$===\n");
            printf("*!:!!=*!;;!!!**$#;,,....,,,..,,,-,-~~****==$$#$===\n");
            printf("!!;*!$*=;;!!!!!=@:,.. ..... ..,,,,,-~=*===$$$$$$==\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf(" \n                  [ HP : %d ]\n ", BossMobHP[1]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf(" \n { 나가기 : 0 }\n"); // 나가기 스페이스바 누르면 한번더 실행 고치기. 모든 Dungeon
            numberDisplayed = 1;
        }
        if (input == '0') {
            printf(" \n 던전을 나갑니다.\n");
            return 0;
        }
        else if (input == '\n') {
            if (messageDisplayed) {
                messageDisplayed = 0;
            }
            else {
                BossMobHP[1] -= JihoPower[level];
                numberDisplayed = 0;
            }
        }
        else {
            if (!messageDisplayed) {
                printf("\n 다시 입력해주세요.\n");
                printf(" {나가기 : 0 }\n");
                messageDisplayed = 1;
            }
        }
    }
    printf(" 으어억...내가 지다니...\n");
    Sleep(1000);
    printf(" 던전 2 완료!\n");
    return 0;
}
void Dungeon3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n 이은임 교수님 : 괜찮아 다시 천천히 해와^^ (자기소개서를 반으로 찟으시면서)\n");
    printf("\n");
    printf("                                                  \n");
    printf("                                                  \n");
    printf("                        ,~;;-                     \n");
    printf("                       -##$$==*-                  \n");
    printf("                      =###@$=$==:                 \n");
    printf("                    ,$#*;!*=#$$=*~                \n");
    printf("                    :#*,,,,,!==$=!-               \n");
    printf("                   -#=,,....-!$==*;               \n");
    printf("                   ~#~,.....,~$==*;,              \n");
    printf("                   !#,,......-====!;              \n");
    printf("                   ;$-~,,,,--~=$$$!!,             \n");
    printf("                   :---,,.,-,-*$=$!:,             \n");
    printf("                   -,~:-..-;;~~=$#$*~             \n");
    printf("                   ,,.,,. .,,..*$$$;;               \n");
    printf("                   ,,..,...... !$##*=              \n");
    printf("                    ,,,~,:-....-$##*!              \n");
    printf("                   --,,,..,,,.,*##!!            \n");
    printf("                   -,---,,,,,.,*##=*-            \n");
    printf("                   :,,-,,,,...,=##=!~          \n");
    printf("                  -#-,,,...,.,,###=*:                 \n");
    printf("                  !#=-,....,,-*#$#$*:             \n");
    printf("                 ,=@@!~-----~!####$=:             \n");
    printf("                 !##@@!***!;!$###@$=;             \n");
    printf("             :#*=#@@@@$*!*$#@@@@#$!==:,           \n");
    printf("             !=#$@@@@#$###=$#@@$*===:;:           \n");
    printf("             =###@@@@**$=$$##$==#!*!:;;           \n");
    printf("           -*$@##@@##*==$=##@=#*$**!;;:;,         \n");
    printf("           !$#@#@@@$$**=$$#@$$=*!!!!;::;~         \n");
    printf("          :=$#@@@##$*==$##@$$=**!!!!!;:;*         \n");
    printf("         -*$$#@@#==$===$$$===*!!;!!;;;!:!-        \n");
    printf("         **=#=#@$$$!====$=#=!;:;!*;*!!;;;,        \n");
    printf("       ~!!=##*@#$$=======$**!;!;;;!!;;;:,          \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf(" \n                [ HP : %d ]\n", BossMobHP[2]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int messageDisplayed = 0;
    int numberDisplayed = 1;
    while (BossMobHP[2] > 0) {
        char input = getchar();
        if (!numberDisplayed) {
            printf("                                                  \n");
            printf("                                                  \n");
            printf("                        ,~;;-                     \n");
            printf("                       -##$$==*-                  \n");
            printf("                      =###@$=$==:                 \n");
            printf("                    ,$#*;!*=#$$=*~                \n");
            printf("                    :#*,,,,,!==$=!-               \n");
            printf("                   -#=,,....-!$==*;               \n");
            printf("                   ~#~,.....,~$==*;,              \n");
            printf("                   !#,,......-====!;              \n");
            printf("                   ;$-~,,,,--~=$$$!!,             \n");
            printf("                   :---,,.,-,-*$=$!:,             \n");
            printf("                   -,~:-..-;;~~=$#$*~             \n");
            printf("                   ,,.,,. .,,..*$$$;;               \n");
            printf("                   ,,..,...... !$##*=              \n");
            printf("                    ,,,~,:-....-$##*!              \n");
            printf("                   --,,,..,,,.,*##!!            \n");
            printf("                   -,---,,,,,.,*##=*-            \n");
            printf("                   :,,-,,,,...,=##=!~          \n");
            printf("                  -#-,,,...,.,,###=*:                 \n");
            printf("                  !#=-,....,,-*#$#$*:             \n");
            printf("                 ,=@@!~-----~!####$=:             \n");
            printf("                 !##@@!***!;!$###@$=;             \n");
            printf("             :#*=#@@@@$*!*$#@@@@#$!==:,           \n");
            printf("             !=#$@@@@#$###=$#@@$*===:;:           \n");
            printf("             =###@@@@**$=$$##$==#!*!:;;           \n");
            printf("           -*$@##@@##*==$=##@=#*$**!;;:;,         \n");
            printf("           !$#@#@@@$$**=$$#@$$=*!!!!;::;~         \n");
            printf("          :=$#@@@##$*==$##@$$=**!!!!!;:;*         \n");
            printf("         -*$$#@@#==$===$$$===*!!;!!;;;!:!-        \n");
            printf("         **=#=#@$$$!====$=#=!;:;!*;*!!;;;,        \n");
            printf("       ~!!=##*@#$$=======$**!;!;;;!!;;;:,          \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf(" \n                [ HP : %d ]\n", BossMobHP[2]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf(" \n { 나가기 : 0 }\n");
            numberDisplayed = 1;
        }
        if (input == '0') {
            printf(" \n 던전을 나갑니다.\n");
            return 0;
        }
        else if (input == '\n') {
            if (messageDisplayed) {
                messageDisplayed = 0;
            }
            else {
                BossMobHP[2] -= JihoPower[level];
                numberDisplayed = 0;
            }
        }
        else {
            if (!messageDisplayed) {
                printf(" 다시 입력해주세요.\n");
                printf(" { 나가기 : 0 }\n");
                messageDisplayed = 1;
            }
        }
    }
    printf(" 으어억...내가 지다니...\n");
    Sleep(1000);
    printf(" 던전 3 완료!\n");
    return 0;
}
void Dungeon4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n 이운석 교수님 : 초등학생도 아는걸 모르는 주제에......\n");
    printf("\n");
    printf("                    :=*!=$.                      \n");
    printf("                   ,*$##$#$$:                     \n");
    printf("                  ,$$##$$$###~                    \n");
    printf("                  =$$##$#####$-                   \n");
    printf("                 ~$$$#$$$$###$$.                  \n");
    printf("                 !=$#$=**$###$$:                  \n");
    printf("                .==$$=!:~;$###$:                  \n");
    printf("                 =##*=*--:=*##$;                  \n");
    printf("                 =$****-~;*!=$*~                  \n");
    printf("                  ==:~;:$::~~~:                   \n");
    printf("                  ;,.--,.;--:.-,                  \n");
    printf("                  :  -,. -:~-...                  \n");
    printf("                  ,   , ,:~~--..                  \n");
    printf("                   ... .,,~:--                    \n");
    printf("                   ...-..:;:--                    \n");
    printf("                      . .---~-                    \n");
    printf("                    ..  .,--~,                    \n");
    printf("                    .,.  ,-~-.                    \n");
    printf("                    ..,,-~;:-.                    \n");
    printf("                   ! ,.,~;;~~ .                   \n");
    printf("                  ~*   .--~~-~-                   \n");
    printf("                .=$*     .~~~;,:                  \n");
    printf("               :$#$#$    -:~:~~=*                 \n");
    printf("             ;=$$$$#$$; ., ~~-.==*~               \n");
    printf("           -$$$$$##$###=,. ~:-=#$#$$$-            \n");
    printf("          ,$$#$$$#######:-,~--######$#=.          \n");
    printf("          =$$$###$#######!.,,$########$*          \n");
    printf("         ,$$$$############!-;##########$;         \n");
    printf("         ~$$$$$#$#@####$################=         \n");
    printf("         ~$$$$##########################*        \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf(" \n                  [ HP : %d ]\n", BossMobHP[3]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int messageDisplayed = 0;
    int numberDisplayed = 1;
    while (BossMobHP[0] > 0) {
        char input = getchar();
        if (!numberDisplayed) {
            printf("                    :=*!=$.                      \n");
            printf("                   ,*$##$#$$:                     \n");
            printf("                  ,$$##$$$###~                    \n");
            printf("                  =$$##$#####$-                   \n");
            printf("                 ~$$$#$$$$###$$.                  \n");
            printf("                 !=$#$=**$###$$:                  \n");
            printf("                .==$$=!:~;$###$:                  \n");
            printf("                 =##*=*--:=*##$;                  \n");
            printf("                 =$****-~;*!=$*~                  \n");
            printf("                  ==:~;:$::~~~:                   \n");
            printf("                  ;,.--,.;--:.-,                  \n");
            printf("                  :  -,. -:~-...                  \n");
            printf("                  ,   , ,:~~--..                  \n");
            printf("                   ... .,,~:--                    \n");
            printf("                   ...-..:;:--                    \n");
            printf("                      . .---~-                    \n");
            printf("                    ..  .,--~,                    \n");
            printf("                    .,.  ,-~-.                    \n");
            printf("                    ..,,-~;:-.                    \n");
            printf("                   ! ,.,~;;~~ .                   \n");
            printf("                  ~*   .--~~-~-                   \n");
            printf("                .=$*     .~~~;,:                  \n");
            printf("               :$#$#$    -:~:~~=*                 \n");
            printf("             ;=$$$$#$$; ., ~~-.==*~               \n");
            printf("           -$$$$$##$###=,. ~:-=#$#$$$-            \n");
            printf("          ,$$#$$$#######:-,~--######$#=.          \n");
            printf("          =$$$###$#######!.,,$########$*          \n");
            printf("         ,$$$$############!-;##########$;         \n");
            printf("         ~$$$$$#$#@####$################=         \n");
            printf("         ~$$$$##########################*        \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf(" \n                  [ HP : %d ]\n", BossMobHP[3]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf(" \n { 나가기 : 0 }\n");
            numberDisplayed = 1;
        }
        if (input == '0') {
            printf(" \n 던전을 나갑니다.\n");
            return 0;
        }
        else if (input == '\n') {
            if (messageDisplayed) {
                messageDisplayed = 0;
            }
            else {
                BossMobHP[3] -= JihoPower[level];
                numberDisplayed = 0;
            }
        }
        else {
            if (!messageDisplayed) {
                printf(" 다시 입력해주세요.\n");
                printf(" { 나가기 : 0 }\n");
                messageDisplayed = 1;
            }
        }
    }
    printf(" 으어억...내가 지다니...\n");
    Sleep(1000);
    printf(" 던전 4 완료!\n");
    return 0;
}
void Dungeon5() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n 김영천 교수님 : 나는 이해가 안돼...\n");
    printf("\n");
    printf("                               .. .,                                  \n");
    printf("                            .,;;~-~~:,,                                \n");
    printf("                           -;#==!*=$$*$-                               \n");
    printf("                           =####==$#$$=!-                              \n");
    printf("                         .!$@#$=!!*=#$$*!.                             \n");
    printf("                        .~=#=:-,-,--:;!===,                            \n");
    printf("                        ,=#*~,,......,-~!$!.                            \n");
    printf("                       .!#$:,,,.........,*=-                            \n");
    printf("                       ;##=-,,...........~$:                            \n");
    printf("                       !@#*-,,..... ......$;                            \n");
    printf("                       *@#!-,,... .... ...=:                            \n");
    printf("                       ,=#@;,,,,,-... ..,..=;                            \n");
    printf("                       ,=~#$-~~~.,~..,,-~,.$,                            \n");
    printf("                       ~,=;-:;;!-;;-~:~:-;!.                            \n");
    printf("                        ,::,,,-~,,;,-~--,$~.                            \n");
    printf("                        ,,-,,..,,--.~,,,..,                             \n");
    printf("                        -,-,,..,-,. ..,,,..                             \n");
    printf("                        .,-,,...,,........                              \n");
    printf("                         =-,,,..~-,..~....                              \n");
    printf("                         !---,,-,,,-,,-,..                              \n");
    printf("                          ~-,,,~~~-,,,-,,                               \n");
    printf("                         .-~,,.-~-..,-,.,.                              \n");
    printf("                         ,~-~-,,,,,,,,,,.                               \n");
    printf("                         ;*----,,--,,,,,                                \n");
    printf("                        ,$#=---,..,,..,.                                \n");
    printf("                       .$##@$~-~,,,..,,;                                \n");
    printf("                      ,*$$#$##*:::~~,,!*.                               \n");
    printf("                     ;*$#$##=##$*!!:-,@$;:                              \n");
    printf("                    ;!$$$$$$$#@###$--:@$=!!~                            \n");
    printf("                 .,;=$$#==$#####@@@=:=@#$*!**,.                          \n");
    printf("                -~*=$$$###$###=#@@@#*$#@$*==$=!~.                        \n");
    printf("               -**=$=$$$$###=$=$#@##$##@$=*===$=!                         \n");
    printf("              .**$=!$=#=#$=$=*=$$=#$#@#=#*===#==$*:                      \n");
    printf("             -=$$==*=#=$$###$!=#===$##==$====$*$$;*~                     \n");
    printf("            ~$$##$$*$###$$##**$$=====#!*$===!$=#$;!*                      \n");
    printf("            !#####*==$$##$$**=$===$*!!#*$*==*$=$$=*!                       \n");
    printf("            ;$###=$$##$=@!$==$$===!=!;:!*$=;*$$=$$$=~                      \n");
    printf("            !#$$#=$$$$=$$$$===##*$$==!:;!==!*#$=$==*!                      \n");
    printf("            ;##$#$*=$$$$=##=$$=!*===$*;~*$=*!$*!*=!=*~                     \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf(" \n                    [ HP : %d ]\n", BossMobHP[4]);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int messageDisplayed = 0;
    int numberDisplayed = 1;
    while (BossMobHP[4] > 0) {
        char input = getchar();
        if (!numberDisplayed) {
            printf("                               .. .,                                  \n");
            printf("                            .,;;~-~~:,,                                \n");
            printf("                           -;#==!*=$$*$-                               \n");
            printf("                           =####==$#$$=!-                              \n");
            printf("                         .!$@#$=!!*=#$$*!.                             \n");
            printf("                        .~=#=:-,-,--:;!===,                            \n");
            printf("                        ,=#*~,,......,-~!$!.                            \n");
            printf("                       .!#$:,,,.........,*=-                            \n");
            printf("                       ;##=-,,...........~$:                            \n");
            printf("                       !@#*-,,..... ......$;                            \n");
            printf("                       *@#!-,,... .... ...=:                            \n");
            printf("                       ,=#@;,,,,,-... ..,..=;                            \n");
            printf("                       ,=~#$-~~~.,~..,,-~,.$,                            \n");
            printf("                       ~,=;-:;;!-;;-~:~:-;!.                            \n");
            printf("                        ,::,,,-~,,;,-~--,$~.                            \n");
            printf("                        ,,-,,..,,--.~,,,..,                             \n");
            printf("                        -,-,,..,-,. ..,,,..                             \n");
            printf("                        .,-,,...,,........                              \n");
            printf("                         =-,,,..~-,..~....                              \n");
            printf("                         !---,,-,,,-,,-,..                              \n");
            printf("                          ~-,,,~~~-,,,-,,                               \n");
            printf("                         .-~,,.-~-..,-,.,.                              \n");
            printf("                         ,~-~-,,,,,,,,,,.                               \n");
            printf("                         ;*----,,--,,,,,                                \n");
            printf("                        ,$#=---,..,,..,.                                \n");
            printf("                       .$##@$~-~,,,..,,;                                \n");
            printf("                      ,*$$#$##*:::~~,,!*.                               \n");
            printf("                     ;*$#$##=##$*!!:-,@$;:                              \n");
            printf("                    ;!$$$$$$$#@###$--:@$=!!~                            \n");
            printf("                 .,;=$$#==$#####@@@=:=@#$*!**,.                          \n");
            printf("                -~*=$$$###$###=#@@@#*$#@$*==$=!~.                        \n");
            printf("               -**=$=$$$$###=$=$#@##$##@$=*===$=!                         \n");
            printf("              .**$=!$=#=#$=$=*=$$=#$#@#=#*===#==$*:                      \n");
            printf("             -=$$==*=#=$$###$!=#===$##==$====$*$$;*~                     \n");
            printf("            ~$$##$$*$###$$##**$$=====#!*$===!$=#$;!*                      \n");
            printf("            !#####*==$$##$$**=$===$*!!#*$*==*$=$$=*!                       \n");
            printf("            ;$###=$$##$=@!$==$$===!=!;:!*$=;*$$=$$$=~                      \n");
            printf("            !#$$#=$$$$=$$$$===##*$$==!:;!==!*#$=$==*!                      \n");
            printf("            ;##$#$*=$$$$=##=$$=!*===$*;~*$=*!$*!*=!=*~                     \n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf(" \n                    [ HP : %d ]\n", BossMobHP[4]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf(" \n { 나가기 : 0 }\n");
            numberDisplayed = 1;
        }
        if (input == '0') {
            printf(" \n 던전을 나갑니다.\n");
            return 0;
        }
        else if (input == '\n') {
            if (messageDisplayed) {
                messageDisplayed = 0;
            }
            else {
                BossMobHP[4] -= JihoPower[level];
                numberDisplayed = 0;
            }
        }
        else {
            if (!messageDisplayed) {
                printf(" 다시 입력해주세요.\n");
                printf(" { 나가기 : 0 }\n");
                messageDisplayed = 1;
            }
        }
    }
    printf(" 으어억...내가 지다니...\n");
    Sleep(1000);
    printf(" 던전 5 완료!\n");
    return 0;
}

int main(void)
{
    srand((unsigned int)time(NULL));         // 랜덤 시드값 설정
    while (!isGameOver)
    {
        system("@cls||clear");      // 화면 정리
        system("mode con cols=200 lines=100 | title 이지호 학생 키우기");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf(" ** 이지호 학생 키우기 **  \n\n");
        // 상태 출력
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        printf(" 학생 레벨 : + %d %s (파워 : %d)\n", level, enhancementMessages1[level], JihoPower[level]);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf(" \n 현재 소지금 : %d원\n", money);
        printf(" 학습 비용 : %d원\n", enhancementCosts[level]);
        printf(" 학습 성공률 : %.2f%%\n", enhancementProbabilitiesStage1[level]);
        printf(" \n 보유 복습권 갯수 : %d\n", tickets);
        printf(" \n 메뉴:\n\n");
        printf(" * 1. 학생 강화하기\n");
        printf(" * 2. 상점가기\n");
        printf(" * 3. 강의실가기\n");
        printf(" * 4. 포기하기\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("\n * 메뉴를 선택하세요 : ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        scanf_s("%d", &isTry);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        switch (isTry)
        {
        case 1:     // 강화에 도전 할 경우
            // 돈이 부족하면 메시지 출력 후 break
            if (money < enhancementCosts[level]) {
                printf("돈이 부족하여 공부 할 수 없습니다.\n");
                break;
            }
            printf("\n  *** 학습중 *** \n\n");
            //Sleep(2000);
            float randNum = (float)rand() / RAND_MAX * 100.0f;
            int i;
            if (randNum < enhancementProbabilitiesStage1[level]) {
                money -= enhancementCosts[level];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                printf(" ***** SUCCESS *****\n");
                printf("                  \n");
                printf("    + %d  -> + %d \n", level, level + 1);
                printf("                  \n");
                printf(" ***** SUCCESS *****\n");
                // 강화에 성공 했을 시, 레벨을 하나 증가 시킴
                level++;
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf(" ***** FAILURE *****\n");
                printf("                  \n");
                printf("      %d  ->  % d    \n", level, level - 1);
                printf("                  \n");
                printf(" ***** FAILURE *****\n");
                printf("\n 어익후.. 핸드폰을 봤네..교수님이 봐버렸다...\n");
                printf("\n [+%d 지식을 잃었습니다.]\n\n", level);
                if (1 <= level <= 20)
                {
                    if (tickets != 0)
                    {
                        money -= enhancementCosts[level];
                        printf("학습에 실패하였습니다. \n현재 학습 수치를 유지하시겠습니까? \n{보유 학습권 갯수 : %d}\n(YES : 1/ NO : 2) : ", tickets);
                        scanf_s("%d", &choice);
                        if (choice == 1) {
                            tickets--;
                            printf("\n복습권을 사용합니다. (보유 복습권 갯수 : %d)\n", tickets);
                            money += enhancementCosts[level];
                        }
                        else if (choice == 2) {
                            printf("학습 수치를 초기화합니다.\n");
                            level = 0; // 강화 수치 초기화
                        }
                        else {
                            printf("잘못된 입력입니다. 다시 선택하세요.\n");
                            continue;
                        }
                    }
                    else
                    {
                        level = 0;
                    }
                }
            }
            // 강화 비용 차감
            break;
        case 2:
            GoStore();
            break;
        case 3:
            printf("\n *** 강의실로 이동 ***\n\n");
            // Sleep(2000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf(" 이곳은 강의실입니다. 교수님들과 면담을 할 수 있습니다.\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("\n 1. 이상현 교수님 (1~4강 추천)\n");
            printf(" 2. 윤소미 교수님 (5~8강 추천)\n");
            printf(" 3. 이은임 교수님 (9강~12강 추천)\n");
            printf(" 4. 이운석 교수님 (13강~16강 추천)\n");
            printf(" 5. 김영천 교수님 (17강~20강 추천)\n\n");
            printf(" 메인화면으로 나가기 - [ 1~5를 제외한 모든 입력키 ]\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf(" 면담하고 싶은 교수님의 번호를 입력하세요 : ");
            scanf_s("%d", &dungeonSelect);
            switch (dungeonSelect) {
            case 1:
                Dungeon1();
                break;
            case 2:
                Dungeon2();
                break;
            case 3:
                Dungeon3();
                break;
            case 4:
                Dungeon4();
                break;
            case 5:
                Dungeon5();
                break;
            default:
                printf("잘못된 입력입니다. 다시 선택하세요.\n");
                break;
            }
            break;
        case 4:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf("\n 이런! 이지호 학생이 자퇴 했습니다 이제 어쩌죠...?\n");
            isGameOver = true; // 게임 종료
            break;
        default:
            printf("잘못된 입력입니다. 다시 선택하세요.\n"); // 엔터 눌러야지 나가기.
            break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("\n 계속하려면 아무 키나 누르세요! \n");
        getchar(); // 개행 문자 처리를 위해 getchar 사용

        // 사용자 입력 대기
        while (getchar() != '\n'); // 버퍼 비우기
    }
    return 0;
}