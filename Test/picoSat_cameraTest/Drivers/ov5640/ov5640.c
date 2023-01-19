#include "ov5640.h"
#include "ov5640cfg.h"
#include "ov5640af.h"			 	
#include "i2c.h"

extern DMA_HandleTypeDef hdma_dcmi;
extern DCMI_HandleTypeDef hdcmi;


uint8_t   jpeg_mode = 0;
uint32_t  jpeg_data_buf[jpeg_buf_size]; 



const uint16_t jpeg_size_tbl[][2]=
{     
    160, 120,	//QQVGA
	176, 144,	//QCIF
	320, 240,	//QVGA
	400, 240,	//WQVGA
	352, 288,	//CIF
};

uint8_t OV5640_WR_Reg(uint16_t reg, uint8_t data)
{

	uint8_t res = 0;
	res = BSP_I2C4_WriteReg16(OV5640_ADDR, reg, &data, 1);
  	return	res;
}


uint8_t OV5640_RD_Reg(uint16_t reg)
{
	uint8_t val=0;
	int32_t ret;
	ret = BSP_I2C4_ReadReg16(OV5640_ADDR, reg, &val, 1);
	if (ret != 0) {
		printf("I2C read error: %d \n", ret);
	}

  	return val;
}
 
uint8_t OV5640_Init(void)
{ 
	uint16_t i=0;
	uint16_t reg;
        
        
 
	OV5640_PWDN_Pin_RESET;		//POWER ON;
        
        HAL_Delay(30); 
              
	reg=OV5640_RD_Reg(OV5640_CHIPIDH);	
	reg<<=8;
	reg|=OV5640_RD_Reg(OV5640_CHIPIDL);
	if(reg!=OV5640_ID)
	{
		printf("ID: %d \r\n",reg);
		return 1;
	}  
	OV5640_WR_Reg(0x3103,0X11);	//system clock from pad, bit[1]
	OV5640_WR_Reg(0X3008,0X82);	
	HAL_Delay(10);
        
	for(i=0;i<sizeof(ov5640_init_reg_tbl)/4;i++)
	{
		OV5640_WR_Reg(ov5640_init_reg_tbl[i][0],ov5640_init_reg_tbl[i][1]);
	} 

         HAL_Delay(50); 
        // Test for flash light
        OV5640_Flash_Lamp(1);
        HAL_Delay(50); 
        OV5640_Flash_Lamp(0);        
               
	return 0x00; 	//ok
} 

void OV5640_JPEG_Mode(void) 
{
	uint16_t i=0; 

	for(i=0;i<(sizeof(OV5640_jpeg_reg_tbl)/4);i++)
	{
		OV5640_WR_Reg(OV5640_jpeg_reg_tbl[i][0],OV5640_jpeg_reg_tbl[i][1]);  
	}  
}

void OV5640_RGB565_Mode(void) 
{
	uint16_t i=0;

	for(i=0;i<(sizeof(ov5640_rgb565_reg_tbl)/4);i++)
	{
		OV5640_WR_Reg(ov5640_rgb565_reg_tbl[i][0],ov5640_rgb565_reg_tbl[i][1]); 
	} 
} 

const static uint8_t OV5640_EXPOSURE_TBL[7][6]=
{
    0x10,0x08,0x10,0x08,0x20,0x10,//-3  
    0x20,0x18,0x41,0x20,0x18,0x10,//-2
    0x30,0x28,0x61,0x30,0x28,0x10,//-1 
    0x38,0x30,0x61,0x38,0x30,0x10,//0  
    0x40,0x38,0x71,0x40,0x38,0x10,//+1 
    0x50,0x48,0x90,0x50,0x48,0x20,//+2   
    0x60,0x58,0xa0,0x60,0x58,0x20,//+3    
};

//exposure: 0 - 6,
void OV5640_Exposure(uint8_t exposure)
{
        OV5640_WR_Reg(0x3212,0x03);	//start group 3
        OV5640_WR_Reg(0x3a0f,OV5640_EXPOSURE_TBL[exposure][0]); 
        OV5640_WR_Reg(0x3a10,OV5640_EXPOSURE_TBL[exposure][1]); 
        OV5640_WR_Reg(0x3a1b,OV5640_EXPOSURE_TBL[exposure][2]); 
        OV5640_WR_Reg(0x3a1e,OV5640_EXPOSURE_TBL[exposure][3]); 
        OV5640_WR_Reg(0x3a11,OV5640_EXPOSURE_TBL[exposure][4]); 
        OV5640_WR_Reg(0x3a1f,OV5640_EXPOSURE_TBL[exposure][5]); 
        OV5640_WR_Reg(0x3212,0x13); //end group 3
        OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

const static uint8_t OV5640_LIGHTMODE_TBL[5][7]=
{ 
	0x04,0X00,0X04,0X00,0X04,0X00,0X00,//Auto 
	0x06,0X1C,0X04,0X00,0X04,0XF3,0X01,//Sunny
	0x05,0X48,0X04,0X00,0X07,0XCF,0X01,//Office
	0x06,0X48,0X04,0X00,0X04,0XD3,0X01,//Cloudy
	0x04,0X10,0X04,0X00,0X08,0X40,0X01,//Home
}; 

// light mode:
//      0: auto
//      1: sunny
//      2: office
//      3: cloudy
//      4: home
void OV5640_Light_Mode(uint8_t mode)
{
	uint8_t i;
	OV5640_WR_Reg(0x3212,0x03);	//start group 3
	for(i=0;i<7;i++)OV5640_WR_Reg(0x3400+i,OV5640_LIGHTMODE_TBL[mode][i]); 
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3	
}

const static uint8_t OV5640_SATURATION_TBL[7][6]=
{ 
	0X0C,0x30,0X3D,0X3E,0X3D,0X01,//-3 
	0X10,0x3D,0X4D,0X4E,0X4D,0X01,//-2	
	0X15,0x52,0X66,0X68,0X66,0X02,//-1	
	0X1A,0x66,0X80,0X82,0X80,0X02,//+0	
	0X1F,0x7A,0X9A,0X9C,0X9A,0X02,//+1	
	0X24,0x8F,0XB3,0XB6,0XB3,0X03,//+2
	0X2B,0xAB,0XD6,0XDA,0XD6,0X04,//+3
}; 


// Color Saturation: 
//   sat:  0 - 6 
void OV5640_Color_Saturation(uint8_t sat)
{ 
	uint8_t i;
	OV5640_WR_Reg(0x3212,0x03);	//start group 3
	OV5640_WR_Reg(0x5381,0x1c);
	OV5640_WR_Reg(0x5382,0x5a);
	OV5640_WR_Reg(0x5383,0x06);
	for(i=0;i<6;i++)  OV5640_WR_Reg(0x5384+i,OV5640_SATURATION_TBL[sat][i]);    
	OV5640_WR_Reg(0x538b, 0x98);
	OV5640_WR_Reg(0x538a, 0x01);
	OV5640_WR_Reg(0x3212, 0x13); //end group 3
	OV5640_WR_Reg(0x3212, 0xa3); //launch group 3	
}

//Brightness
//     bright:  0 - 8
void OV5640_Brightness(uint8_t bright)
{
	uint8_t brtval;
	if(bright<4)brtval=4-bright;
	else brtval=bright-4;
	OV5640_WR_Reg(0x3212,0x03);	//start group 3
	OV5640_WR_Reg(0x5587,brtval<<4);
	if(bright<4)OV5640_WR_Reg(0x5588,0x09);
	else OV5640_WR_Reg(0x5588,0x01);
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

//Contrast:
//     contrast:  0 - 6
void OV5640_Contrast(uint8_t contrast)
{
	uint8_t reg0val=0X00;
	uint8_t reg1val=0X20;
	switch(contrast)
	{
		case 0://-3
			reg1val=reg0val=0X14;	 	 
			break;	
		case 1://-2
			reg1val=reg0val=0X18; 	 
			break;	
		case 2://-1
			reg1val=reg0val=0X1C;	 
			break;	
		case 4://1
			reg0val=0X10;	 	 
			reg1val=0X24;	 	 
			break;	
		case 5://2
			reg0val=0X18;	 	 
			reg1val=0X28;	 	 
			break;	
		case 6://3
			reg0val=0X1C;	 	 
			reg1val=0X2C;	 	 
			break;	
	} 
	OV5640_WR_Reg(0x3212,0x03); //start group 3
	OV5640_WR_Reg(0x5585,reg0val);
	OV5640_WR_Reg(0x5586,reg1val); 
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}
// Sharpness:
//    sharp: 0 - 33   (0: close , 33: auto , other: Sharpness)

void OV5640_Sharpness(uint8_t sharp)
{
	if(sharp<33)
	{
		OV5640_WR_Reg(0x5308,0x65);
		OV5640_WR_Reg(0x5302,sharp);
	}else	// auto
	{
		OV5640_WR_Reg(0x5308,0x25);
		OV5640_WR_Reg(0x5300,0x08);
		OV5640_WR_Reg(0x5301,0x30);
		OV5640_WR_Reg(0x5302,0x10);
		OV5640_WR_Reg(0x5303,0x00);
		OV5640_WR_Reg(0x5309,0x08);
		OV5640_WR_Reg(0x530a,0x30);
		OV5640_WR_Reg(0x530b,0x04);
		OV5640_WR_Reg(0x530c,0x06);
	}
	
}

const static uint8_t OV5640_EFFECTS_TBL[7][3]=
{ 
		0X06,0x40,0X10, // normal
		0X1E,0xA0,0X40,
		0X1E,0x80,0XC0,
		0X1E,0x80,0X80,
		0X1E,0x40,0XA0,
		0X40,0x40,0X10,
		0X1E,0x60,0X60,
}; 
	    
void OV5640_Special_Effects(uint8_t eft)
{ 
	OV5640_WR_Reg(0x3212,0x03); //start group 3
	OV5640_WR_Reg(0x5580,OV5640_EFFECTS_TBL[eft][0]);
	OV5640_WR_Reg(0x5583,OV5640_EFFECTS_TBL[eft][1]);// sat U
	OV5640_WR_Reg(0x5584,OV5640_EFFECTS_TBL[eft][2]);// sat V
	OV5640_WR_Reg(0x5003,0x08);
	OV5640_WR_Reg(0x3212,0x13); //end group 3
	OV5640_WR_Reg(0x3212,0xa3); //launch group 3
}

// Flash Lamp
//  sw:  0: off
//       1:  on
void OV5640_Flash_Lamp(uint8_t sw)
{
	OV5640_WR_Reg(0x3016,0X02);
	OV5640_WR_Reg(0x301C,0X02); 
	if(sw)OV5640_WR_Reg(0X3019,0X02); 
	else OV5640_WR_Reg(0X3019,0X00);
} 

// set the output size
uint8_t OV5640_OutSize_Set(uint16_t offx,uint16_t offy,uint16_t width,uint16_t height)
{ 
        OV5640_WR_Reg(0X3212,0X03);  	

        OV5640_WR_Reg(0x3808,width>>8);	
        OV5640_WR_Reg(0x3809,width&0xff);
        OV5640_WR_Reg(0x380a,height>>8);
        OV5640_WR_Reg(0x380b,height&0xff);

        OV5640_WR_Reg(0x3810,offx>>8);	
        OV5640_WR_Reg(0x3811,offx&0xff);

        OV5640_WR_Reg(0x3812,offy>>8);	
        OV5640_WR_Reg(0x3813,offy&0xff);

        OV5640_WR_Reg(0X3212,0X13);		
        OV5640_WR_Reg(0X3212,0Xa3);		
        
        return 0; 
}


uint8_t OV5640_Focus_Init(void)
{ 
	uint16_t i; 
	uint16_t addr=0x8000;
	uint8_t state=0x8F;
	OV5640_WR_Reg(0x3000, 0x20);	//reset 	 
	for(i=0;i<sizeof(OV5640_AF_Config);i++) 
	{
		OV5640_WR_Reg(addr,OV5640_AF_Config[i]);
		addr++;
	}  
	OV5640_WR_Reg(0x3022,0x00);
	OV5640_WR_Reg(0x3023,0x00);
	OV5640_WR_Reg(0x3024,0x00);
	OV5640_WR_Reg(0x3025,0x00);
	OV5640_WR_Reg(0x3026,0x00);
	OV5640_WR_Reg(0x3027,0x00);
	OV5640_WR_Reg(0x3028,0x00);
	OV5640_WR_Reg(0x3029,0x7f);
	OV5640_WR_Reg(0x3000,0x00); 
	i=0;
	do
	{
		state=OV5640_RD_Reg(0x3029);	
		HAL_Delay(5);
		i++;
		if(i>1000)return 1;
	}while(state!=0x70); 
	return 0;    
}  

uint8_t OV5640_Auto_Focus(void)
{
	uint8_t temp=0;   
	uint16_t retry=0; 
	OV5640_WR_Reg(0x3023,0x01);
	OV5640_WR_Reg(0x3022,0x08);
	do 
	{
		temp=OV5640_RD_Reg(0x3023); 
		retry++;
		if(retry>1000)return 2;
		HAL_Delay(5);
	} while(temp!=0x00);   
	OV5640_WR_Reg(0x3023,0x01);
	OV5640_WR_Reg(0x3022,0x04);
	retry=0;
	do 
	{
		temp=OV5640_RD_Reg(0x3023); 
		retry++;
		if(retry>1000)return 2;
		HAL_Delay(5);
	}while(temp!=0x00);
	return 0;
} 


