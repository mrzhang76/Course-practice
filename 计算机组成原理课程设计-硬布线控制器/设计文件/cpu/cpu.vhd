LIBRARY ieee;

USE ieee.std_logic_1164.all;

 

ENTITY cpu IS

PORT(SW:IN std_logic_vector(2 Downto 0);            --������ʽ����׶�

 IR:IN std_logic_vector(7 Downto 4);

 W1,W2,W3:IN std_logic;

 C,Z,CLR,T3:IN std_logic;

 ARINC,CIN,DRW,LPC,LAR,LIR,LDZ,LDC,PCINC,PCADD,SELCTL,M,MEMW,STOP:OUT std_logic;

 SHORT,LONG,ABUS,SBUS,MBUS:OUT std_logic;

 S,SEL:OUT std_logic_vector(3 Downto 0));    

END cpu;

 

ARCHITECTURE cont OF cpu IS

SIGNAL ST0:std_logic;

SIGNAL SST0:std_logic;

BEGIN

PROCESS(ST0,SST0,SW,IR,CLR,T3,W1,W2,W3)   --�����źű�

BEGIN

IF (CLR='0') THEN                     --clear�ź�

ST0<='0';

SST0<='0';

CIN<='0';                             --��ʼֵ

DRW<='0';

LPC<='0';

LAR<='0';

LIR<='0';

LDZ<='0';

LDC<='0';

PCINC<='0';

PCADD<='0';

SELCTL<='0';

M<='0';

S<="0000";

SEL<="0000";

MEMW<='0';

STOP<='0';

SHORT<='0';

LONG<='0';

ABUS<='0';

SBUS<='0';

MBUS<='0';

ARINC<='0';

ELSE

CIN<='0';                              --��ʼֵ

DRW<='0';

LPC<='0';

LAR<='0';

LIR<='0';

LDZ<='0';

LDC<='0';

PCINC<='0';

PCADD<='0';

SELCTL<='0';

M<='0';

S<="0000";

SEL<="0000";

MEMW<='0';

STOP<='0';

SHORT<='0';

LONG<='0';

ABUS<='0';

SBUS<='0';

MBUS<='0';

ARINC<='0';

SST0<=(NOT ST0)AND ((SW(2)AND(NOT(SW(1)))AND(NOT SW(0))AND W2)OR((NOT SW(2))AND SW(1)AND(NOT SW(0))AND W1)OR((NOT SW(2))

         AND (NOT SW(1)) AND SW(0) AND W1));

--��������ʽ��ʾSST0

IF(SST0='1' ) THEN

IF (T3'EVENT AND (T3='0'))THEN --T3�½���

ST0<='1';

END IF;

END IF;

CASE SW IS

--����Ӳ���߿������ο�����ͼ�������̵���ʽ

WHEN "100" =>   --д�Ĵ���

IF (ST0='0') THEN

IF (W1='1') THEN

SBUS<='1';

SEL<="0011";

SELCTL<='1';

DRW<='1';

STOP<='1';

END IF;

IF (W2='1') THEN

SBUS<='1';

SEL<="0100";

SELCTL<='1';

DRW<='1';

STOP<='1';

SST0<='1';

END IF;

END IF;

IF (ST0='1') THEN

   IF (W1='1') THEN

SBUS<='1';

SEL<="1001";

SELCTL<='1';

DRW<='1';

STOP<='1';

END IF;

IF (W2='1') THEN

SBUS<='1';

SEL<="1110";

SELCTL<='1';

DRW<='1';

STOP<='1';

END IF;

END IF;

WHEN "011" =>                 --���Ĵ���

IF (W1='1') THEN

SEL<="0001";

SELCTL<='1';

STOP<='1';

END IF;

IF (W2='1') THEN

SEL<="1011";

SELCTL<='1';

STOP<='1';

END IF;

WHEN "010"=> --���洢��

IF (ST0='0') THEN

IF (W1='1') THEN

SBUS<='1';

LAR<='1';

STOP<='1';

SHORT<='1';

SELCTL<='1';

SST0<='1';

END IF;

END IF;

IF (ST0='1') THEN

IF (W1='1') THEN

MBUS<='1';

ARINC<='1';

STOP<='1';

SHORT<='1';

SELCTL<='1';

END IF;

END IF;

WHEN "001"=> --д�洢��

IF (ST0='0') THEN

IF (W1='1') THEN

SBUS<='1';

LAR<='1';

STOP<='1';

SHORT<='1';

SELCTL<='1';

SST0<='1';

END IF;

END IF;

IF (ST0='1') THEN

IF (W1='1') THEN

SBUS<='1';

MEMW<='1';

ARINC<='1';

STOP<='1';

SHORT<='1';

SELCTL<='1';

END IF;

END IF;

WHEN "000"=> --ȡָ

IF (W1='1') THEN

LIR<='1';

PCINC<='1';

END IF;

CASE IR IS

WHEN "0001"=> --ADD

IF (W2='1') THEN

S<="1001";

CIN<='1';

ABUS<='1';

DRW<='1';

LDZ<='1';

LDC<='1';

END IF;

WHEN "0010"=> --SUB

IF (W2='1') THEN

S<="0110";

ABUS<='1';

DRW<='1';

LDZ<='1';

LDC<='1';

END IF;

WHEN "0011"=> --AND

IF (W2='1') THEN

M<='1';

S<="1011";

ABUS<='1';

DRW<='1';

LDZ<='1';

END IF;

WHEN "0100"=> --INC

IF (W2='1') THEN

S<="0000";

ABUS<='1';

DRW<='1';

LDZ<='1';

LDC<='1';

END IF;

WHEN "0101"=> --LD

IF (W2='1') THEN

M<='1';

S<="1010";

ABUS<='1';

LAR<='1';

LONG<='1';

END IF;

IF (W3='1') THEN

DRW<='1';

MBUS<='1';

END IF;

WHEN "0110"=> --ST

IF (W2='1') THEN

M<='1';

S<="1111";

ABUS<='1';

LAR<='1';

LONG<='1';

END IF;

IF (W3='1') THEN

S<="1010";

M<='1';

ABUS<='1';

MEMW<='1';

END IF;

WHEN "0111"=> --JC

IF (W2='1') THEN

IF (C='1') THEN

PCADD<='1';

END IF;

END IF;

WHEN "1000"=> --JZ

IF (W2='1') THEN

IF (Z='1') THEN

PCADD<='1';

END IF;

END IF;

WHEN "1001"=> --JMP

IF (W2='1') THEN

M<='1';

S<="1111";

ABUS<='1';

LPC<='1';

END IF;

WHEN "1010"=> --OUT

IF (W2='1') THEN

M<='1';

S<="1010";

ABUS<='1';

END IF;
WHEN "1011"=> --ADD ITEMSELF

IF (W2='1') THEN

S<="1100";

CIN<='1';

ABUS<='1';

DRW<='1';

LDC<='1';

LDZ<='1';

END IF;

WHEN "1100"=> --XOR

IF (W2='1') THEN

M<='1';

S<="0110";

ABUS<='1';

DRW<='1';

LDZ<='1';

END IF;

WHEN "1101"=> --OR

IF (W2='1') THEN

M<='1';

S<="1110";

ABUS<='1';

DRW<='1';

LDZ<='1';

END IF;

WHEN "1111"=> --WOR

IF (W2='1') THEN

M<='1';

S<="1001";

ABUS<='1';

DRW<='1';

LDZ<='1';

END IF;

WHEN "1110"=> --STP

IF (W2='1') THEN

STOP<='1';

END IF;

WHEN OTHERS=>SBUS<='0';

END CASE;

WHEN OTHERS=>SBUS<='0';

END CASE;

END IF;

END PROCESS;

END cont;