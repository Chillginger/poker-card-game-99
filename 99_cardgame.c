#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	//R是隨機數 T是決定bot或player的回合 xx_cards是xx擁有的牌數&xx出了幾張牌、要補幾張牌 xx_crad_num是xx出的牌的數字 xx_handcards是xx當前的手牌//
	//Sea是總和、海 num是出的牌 win是判斷誰贏了 nice是防止玩家空想牌 Deck是牌庫 check是看牌庫有無四張一樣的牌//
	//暫時性變數n d i o//
	int Sea = 0, num;
	int P_card_num=0, P_cards=5, P_choose;
	int nice=1, check =0, count=0, Deck_Set=0;
	int P_handcards[5]={0};
	int Bot_card_num=0, Bot_cards=5, Bot_choose;
	int Bot_handcards[5]={0};
	int Deck[52]={0};
	int win, T;
	int R =0;
	int ACE = 0;
	srand(time(NULL));
	printf("Card game : 99!\n");
//決定bot先手還是player先手//
	T = rand()%2 +1;
	if (T==2){
		printf("Bot first!\n");
	}
	else{
		printf("Player first!\n");
	}
//以下是遊戲開始後的迴圈//
	while(1){
		//以下是抽卡環節//
		for(int card_num = R ; P_cards != 0 || Bot_cards != 0; R= 0){
	    //以下是取R=1~13其中一個數字，機率1/13//
			while(check == 0){
				R = rand()%13 + 1;
				count =0;
				//查看牌庫//
				for(int n =0 ; n<52; ++n){
					if(Deck[n] == 0 || Deck[n] == 99){
						Deck[n] = R;
						check = 1;
						break;
					}
					else if(Deck[n] == R%14){
						++count;
					}
					else if(Deck_Set == 13){
							for(int d =0; d<52; ++d){
								Deck[d]=0;
								}
								Deck_Set=0;
								break;
							}
					else if(count == 4){
						++Deck_Set;
						break;
					}
				}
			}
			check=0;
			if(R == 1){
				if((rand()%100)%25 == 0){
					R = 15;
					ACE = 1;
				}
			}
	    	if(Bot_cards != 0){
				Bot_card_num = R;
				if (Bot_handcards[Bot_choose] == 99)
				{
					Bot_handcards[Bot_choose] = Bot_card_num;
					break;
				}
				else{
					Bot_handcards[Bot_cards - 1] = Bot_card_num;
				}
	    		--Bot_cards;
	    	}
	    	else if(Bot_cards == 0){
				P_card_num = R;
				if (P_handcards[P_choose] == 99)
				{
					P_handcards[P_choose] = P_card_num;
					break;
				}
				else{
					P_handcards[P_cards - 1] = P_card_num;
				}
	    		--P_cards;
	    	}
		}
		R = 0;
		//註記抽到什麼牌，然後形成一個「牌庫」，在被「抽乾」時才會「刷新」//
		//Bot出牌//
		if (T==2)
		{
			printf("Bot's turn!\n");
			Bot_choose=rand()%10%5;
			Bot_card_num = Bot_handcards[Bot_choose];
			Bot_handcards[Bot_choose] = 99;
			num = Bot_card_num;
			++Bot_cards;
		}
		//玩家出牌//
		else if(T==1)
		{
			nice=1;
			while(nice == 1){
				printf("Player's trun!\n");
				printf("you got: ");
				for(int i = 0; i<5; ++i){
					printf("%d ", P_handcards[i]);
				}
				printf("\nchoose one card:");
				scanf("%d", &P_card_num);
				for(int o = 0; o<5; ++o){
					if(P_handcards[o] == P_card_num){
						P_choose = o;
						P_handcards[o] = 99;
						++P_cards;
						nice =0;
						break;
					}
				}
				if(nice == 1){
					printf("choose the card in your deck!\n");
				}
			}
			num = P_card_num;
		}
		//數字對應的功能、效果//
		//處理效果//
		switch(num)
		{
		case 15:
			Sea = 0;
			ACE = 0;
			break;
		case 1:
		case 2:
		case 3:
		case 6:
		case 7:
		case 8:
		case 9:
			Sea += num;
			break;
		case 4:
			break;
		case 5:
			break;
		case 10:
			if(T==2)
			{
				if(rand()%10%2 == 0 && Sea > 10 || Sea > 89)
				{
					num = -10;
				}
				else
				{
					num = 10;
				}
			}
			else
			{
				if(Sea >10 && Sea < 90){
					printf("'+10' or '-10'? :");
					scanf("%d", &num);
				}
				else if(Sea >89){
					num = -10;
				}
				else{
					num =10;
				}
			}
			Sea = Sea + num;
			break;
		case 11:
			break;
		case 12:
			if(T==2)
			{
				if(rand()%10%2 == 0 && Sea > 20 || Sea > 79)
				{
					num = -20;
				}
				else
				{
					num = 20;
				}
			}
			else
			{
				if(Sea >20 && Sea <80){
					printf("'+20' or '-20'? :");
					scanf("%d", &num);
				}
				else if(Sea >79){
					num = -20;
				}
				else{
					num = 20;
				}
			}
			Sea = Sea + num;
			break;
		case 13:
			Sea = 99;
			break;
		default:
			printf("error:effect_process");
			return 0;
		}
		//計算海之後的總和//
		printf("Sea = %d\n", Sea);
		//判斷海有沒有超過99？如果有，是誰贏？//
	    if(Sea>99){
			win = T % 2 + 1;
			break;
        }
		//加註標籤方便bot運行//
		//抽牌換下一位//
		T = T % 2 + 1;
    }
//輸出誰贏誰輸的訊息//
	if(win==1){
			printf("Player win!");
	}
	else if(win==2){
		printf("Bot win!");
	}
	return 0;
}