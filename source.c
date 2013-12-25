#include <at89x52.h>
#include "box.h"
unsigned int TIMEOUT = TIMEOUT_default;
unsigned int timer_count = 0;
unsigned int sm_5_si;
unsigned int time_color = 0;
unsigned int time_sun = 0;
unsigned char left_right = 0;
unsigned char ten = 9;
unsigned char single = 9;
unsigned int sun_show_it = num_left[0];
unsigned char i = 0;
unsigned char rev_number_back = 3;
unsigned char goal_num = 0;
unsigned char goal_color_light = ALL_STOP;
unsigned int core_count = 0;
unsigned int core_pre_count = 0;



void display_sun(unsigned int rev_number);
void display_color_light(void);
void interrupt_startup(void) __interrupt(1);
void num_agent(void);
//unsigned char update_switch(void)
void update_switch(void);

void main(void)
{
    interrupt_init();
    update_switch();
    P0 = 0x81;
    for(;;){
        num_agent();
        display_color_light();

	}
}



void interrupt_startup(void) __interrupt(1)
{
	TH0 = TH_VAL;
	TL0 = TL_VAL;

	if (++timer_count == TIMEOUT){
		  timer_count = 0;
        ++time_color;
        ++sm_5_si;

	}
    if(++core_pre_count >= time_out_1s){
        ++core_count;
        core_pre_count = 0;
    }


    if(core_count == startup[i].display_count){
        i = (i > n_ele_startup) ? 1 : i;
        ++i;
        goal_num = startup[i].display_value;
        goal_color_light = startup[i].display_value;
        rev_number_back = startup[i].display_count;
        core_count = 0;;
       update_switch();

    }

}

void display_sun(unsigned int show_num )
{
       if( (show_num >= 100) && (show_num <= 0)){
           show_num  = 99;
            ten = 9;
            single =9;
       }

        ten = show_num / 10;
        single = show_num % 10;
       

       if(left_right % 2){
            sun_show_it = num_left[ten];
       }else{
            sun_show_it = num_right[single];
       }

       P1 = sun_show_it;
       ++left_right;

}

void display_color_light(void)
{
        P0 = goal_color_light;
}

void num_agent(void)
{
    if(sm_5_si >= time_out_1s){
        --rev_number_back;
        sm_5_si = 0;
    }else if(sm_5_si < time_out_1s){
        ;
    }

    display_sun(rev_number_back);

}
