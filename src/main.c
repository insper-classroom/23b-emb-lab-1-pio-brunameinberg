/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

//Utilizando a placa OLED1: 
//botão 1 ->  pin 9 -> pd 28
//botão 2 -> pin 3 -> pc 31
//botão 3 -> pin 4 -> pa 19

//led 1 -> pin 7 -> pa 0
//led 2 -> pin 8 -> pc 30
//led 3 -> pin 6 ->pb 2

#define LED_PIO_1      PIOA     //Periférico que controla o led
#define LED_PIO_ID_1		ID_PIOA	  // ID do periférico PIOA (controla LED)
#define LED_PIO_IDX_1     0	  //ID do led no fio  
#define LED_PIO_IDX_MASK_1 1 << LED_PIO_IDX_1	  //Mascara para controlarmos o LED

#define LED_PIO_2      PIOC     
#define LED_PIO_ID_2		ID_PIOC	  
#define LED_PIO_IDX_2     30	  
#define LED_PIO_IDX_MASK_2 1 << LED_PIO_IDX_2	  

#define LED_PIO_3      PIOB     
#define LED_PIO_ID_3		ID_PIOB	  
#define LED_PIO_IDX_3     2	  
#define LED_PIO_IDX_MASK_3 1 << LED_PIO_IDX_3	  


// Configuraçõoes do botao
#define BUT_PIO_1		PIOD     //Periférico que controla o botão
#define BUT_PIO_ID_1	ID_PIOD	 //ID do periférico que controla o PIOD
#define BUT_PIO_IDX_1		28	 //ID do botao que controla o fio 
#define BUT_PIO_IDX_MASK_1 (1u << BUT_PIO_IDX_1)  //Mascara para controlar o botao

#define BUT_PIO_2		PIOC
#define BUT_PIO_ID_2	ID_PIOC
#define BUT_PIO_IDX_2		31
#define BUT_PIO_IDX_MASK_2 (1u << BUT_PIO_IDX_2) 

#define BUT_PIO_3		PIOA
#define BUT_PIO_ID_3	ID_PIOA
#define BUT_PIO_IDX_3		19
#define BUT_PIO_IDX_MASK_3 (1u << BUT_PIO_IDX_3) 



/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void)
{
	//Initialize the board clock
	sysclk_init();
	
	//Desativa WatchDog Timer;
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID_1);
	pmc_enable_periph_clk(LED_PIO_ID_2);
	pmc_enable_periph_clk(LED_PIO_ID_3);
	
	pio_set_output(LED_PIO_1, LED_PIO_IDX_MASK_1, 0, 0, 0); //Configura o index X (LED_PIO_IDX) do PIOX como sendo saída inicializada com o valor '0', sem multidrive e sem resistor de pull-up.
	pio_set_output(LED_PIO_2, LED_PIO_IDX_MASK_2, 0, 0, 0);
	pio_set_output(LED_PIO_3, LED_PIO_IDX_MASK_3, 0, 0, 0);
	
	pmc_enable_periph_clk(BUT_PIO_ID_1);
	pmc_enable_periph_clk(BUT_PIO_ID_2);
	pmc_enable_periph_clk(BUT_PIO_ID_3);
	
	pio_set_input(BUT_PIO_1, BUT_PIO_IDX_MASK_1, PIO_DEFAULT);
	pio_pull_up(BUT_PIO_1, BUT_PIO_IDX_MASK_1, BUT_PIO_IDX_MASK_1);
	pio_set_input(BUT_PIO_2, BUT_PIO_IDX_MASK_2, PIO_DEFAULT);
	pio_pull_up(BUT_PIO_2, BUT_PIO_IDX_MASK_2, BUT_PIO_IDX_MASK_2);
	pio_set_input(BUT_PIO_3, BUT_PIO_IDX_MASK_3, PIO_DEFAULT);
	pio_pull_up(BUT_PIO_3, BUT_PIO_IDX_MASK_3, BUT_PIO_IDX_MASK_3);
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	
  init();

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	  //Verifica valor do pino que o botão está conectado
	  if(!pio_get(BUT_PIO_1, PIO_INPUT, BUT_PIO_IDX_MASK_1)){

			pio_set(LED_PIO_1, LED_PIO_IDX_MASK_1); //coloca 1 no pino LED
			delay_ms(100); //delay por software de 200 ms
			pio_clear(LED_PIO_1, LED_PIO_IDX_MASK_1); //coloca 0 no pino do LED
			delay_ms(100); //delay por software de 200 ms
	  
	  }
	  if(!pio_get(BUT_PIO_2, PIO_INPUT, BUT_PIO_IDX_MASK_2)){

		  pio_set(LED_PIO_2, LED_PIO_IDX_MASK_2); //coloca 1 no pino LED
		  delay_ms(100); //delay por software de 200 ms
		  pio_clear(LED_PIO_2, LED_PIO_IDX_MASK_2); //coloca 0 no pino do LED
		  delay_ms(100); //delay por software de 200 ms
		  
	  }
	  if(!pio_get(BUT_PIO_3, PIO_INPUT, BUT_PIO_IDX_MASK_3)){

		  pio_set(LED_PIO_3, LED_PIO_IDX_MASK_3); //coloca 1 no pino LED
		  delay_ms(100); //delay por software de 200 ms
		  pio_clear(LED_PIO_3, LED_PIO_IDX_MASK_3); //coloca 0 no pino do LED
		  delay_ms(100); //delay por software de 200 ms
		  
	  }
	   else{
		  //ativa o pino LED_IDX (para apagar)
		  pio_set(LED_PIO_1, LED_PIO_IDX_MASK_1);
		  pio_set(LED_PIO_2, LED_PIO_IDX_MASK_2);
		  pio_set(LED_PIO_3, LED_PIO_IDX_MASK_3);
	  }

  }
  return 0;
}
