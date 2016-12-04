# �������� �����������
�������� ����� �� �������� "�������������-����������� �������".
### ������
- Google Drive ���������� � ����������� ������� [[link](https://drive.google.com/drive/folders/0B8BBveUPbuVYdWFFa1RsMThxa3M)]
- ������ �� ������ [[link](http://embedded.ifmo.ru/forum/viewforum.php?f=9)]
- ������� �� �������� [[link](http://embedded.ifmo.ru/forum/download/file.php?id=814)]
- ����������� � ����������� [[link](https://github.com/bildeyko/calc_sdk1.1)]
- ������ �� GM3P [[link](http://embedded.ifmo.ru/sdk/sdk11/soft/gm3p/gm3p_user_manual.pdf)]
- ������������ � ������������ SDK-1.1 [[link](http://embedded.ifmo.ru/index.php/support/sdk-11)]
- ������������ ������� �� SDK-1.1 �� ���� [[link](http://study.urfu.ru/Aid/Publication/12118/1/Kovalev.pdf)]

### �����

#### ���� 1. ���������� ������������ �������.
������������� �����. ��������� ��������� ����� ������������ ����������� ������� (���, ������������, �������) �� ��������� ���� �������� ������. �������� � �������� �������� ���� ����������� �������, �������� �� ������������ � ����������.

#### ���� 2. ���������� ����������� ���
��������� ������� � ��������� ����� ������ ����������� ��������������� ���.  
� ����� ������ _������������_: ����������� ������������, ������ ������ � ��������� �������; ��������, ����������, � �.�.  
� ����� ������ _������������_: ������������ ������ � ������ ����������������, ������� ���������� ��������� �����������
�����������; ����������� �� ������� ��� � �������� ���������� � ������������; ����������� ���������� ���������������� ���; ��������� ������������ ����������� � ���������������� ��� ���������.  
���������� ��������� � �����, ����������� ��� ��������� ������������ ����������� ���.
�������� ����������� ������������� ��������� � ������� �������� ����� ������������� UML

#### ���� 3. ���������� ������������ �����������.
���������� �������� ������������ ����������� ��������������� ���, �������� ������ ���������� ��������� ������� ��������� � �������� ���������, �� ��������������.

#### ���� 4. ������� � ������������ ������������� ������������ �����������.
���������� �������� �������� ������� � ������������ ������������ ����������� ��������������� ��� (���������� ������, ���� ���������).  
���������� ������ ������, ����������� ������� ����� � ���, ��� ��� ������������� �������� ����������� (�������� �� ������������ � ��������� ����������).

### ������  
#### ������ ������� hex �����, ���������� � Keil  
1. Keil ������ ��� ������� ���������� Objects, � ������� ����� calk.hex  
2. ��������� install.bat  

#### ���������� �51  
**���������, ��������� ����� ��������, �������� ����������� � ��������������!**   
1. � build.bat ������� ��������� ���� � ����������� �51 - ���������� CDIR  
2. ��������� build.bat  
3. ���������, ����� ��������������� hex->bin ����� � ������� ��������� ����� ������ 0x2100    
4. ��������� ������ ����� � ���������� bin   
5. ��������� ����� compile.msg � link.msg �� ������� ������.

��������� ������ �� ������� ������ ���� �������� ���������  

```
����������� ������:         1.
���������� ����������� ��������� ������ � ���� ����.

OBJECT TO HEX FILE CONVERTER OH51 V2.7.0.0
COPYRIGHT KEIL ELEKTRONIK GmbH 1991 - 2001

GENERATING INTEL HEX FILE: calk.hex

OBJECT TO HEX CONVERSION COMPLETED.
** M3P v 1.8.5a

Hex->Bin ���������, ������ ��� ������ ��� ������ �������� 64�!
���� HEX       : calk.hex
���� BIN       : calk.bin
��������� �����: 0x2100** M3P v 1.8.5a
Open script file load.m3p

Open channel:com3 9600
�� ���� ������� ����!
```

#### ���������� SDCC
1. ������� SDCC [[link](http://embedded.ifmo.ru/sdk/sdk11/soft/sdcc/sdcc-2.9.0-setup.exe)].  ������ ������ 2.9.0, �� ������� > 3.0 ������� �� ����������  
2. make.exe ����� � ./UTILS, �������� ��� ���������� � path  
3. make  
4. ��������� ������ ����� � ����� ���������� 
   
make - ������ �������  
make clean - �������   
make load - �������� ������� � ������� �����  
make term - ����� ��������� ���������  
make dist - ���������� ������ tar.gz  
