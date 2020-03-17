EESchema Schematic File Version 4
LIBS:ESP12-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ESP07-8266 Wifi Modul"
Date "2019-04-03"
Rev ""
Comp "Autor: Oliver Hollý"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+3V3 #PWR0101
U 1 1 5C8BF3B6
P 4250 2550
F 0 "#PWR0101" H 4250 2400 50  0001 C CNN
F 1 "+3V3" H 4265 2723 50  0000 C CNN
F 2 "" H 4250 2550 50  0001 C CNN
F 3 "" H 4250 2550 50  0001 C CNN
	1    4250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2550 4250 2950
$Comp
L power:GND #PWR0102
U 1 1 5C8BF42B
P 4250 4700
F 0 "#PWR0102" H 4250 4450 50  0001 C CNN
F 1 "GND" H 4255 4527 50  0000 C CNN
F 2 "" H 4250 4700 50  0001 C CNN
F 3 "" H 4250 4700 50  0001 C CNN
	1    4250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4700 4250 4450
$Comp
L Regulator_Linear:NCP1117-3.3_SOT223 U3
U 1 1 5C8BF558
P 9950 1200
F 0 "U3" H 9950 1442 50  0000 C CNN
F 1 "NCP1117-3.3_SOT223" H 9950 1351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 9950 1400 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/NCP1117-D.PDF" H 10050 950 50  0001 C CNN
	1    9950 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5C8BF5F9
P 9950 1650
F 0 "#PWR0103" H 9950 1400 50  0001 C CNN
F 1 "GND" H 9955 1477 50  0000 C CNN
F 2 "" H 9950 1650 50  0001 C CNN
F 3 "" H 9950 1650 50  0001 C CNN
	1    9950 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5C8BF60F
P 9400 1650
F 0 "#PWR0104" H 9400 1400 50  0001 C CNN
F 1 "GND" H 9405 1477 50  0000 C CNN
F 2 "" H 9400 1650 50  0001 C CNN
F 3 "" H 9400 1650 50  0001 C CNN
	1    9400 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5C8BF61E
P 10500 1650
F 0 "#PWR0105" H 10500 1400 50  0001 C CNN
F 1 "GND" H 10505 1477 50  0000 C CNN
F 2 "" H 10500 1650 50  0001 C CNN
F 3 "" H 10500 1650 50  0001 C CNN
	1    10500 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5C8BF64B
P 9250 1100
F 0 "#PWR0106" H 9250 950 50  0001 C CNN
F 1 "+5V" H 9265 1273 50  0000 C CNN
F 2 "" H 9250 1100 50  0001 C CNN
F 3 "" H 9250 1100 50  0001 C CNN
	1    9250 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0107
U 1 1 5C8BF687
P 10650 1100
F 0 "#PWR0107" H 10650 950 50  0001 C CNN
F 1 "+3V3" H 10665 1273 50  0000 C CNN
F 2 "" H 10650 1100 50  0001 C CNN
F 3 "" H 10650 1100 50  0001 C CNN
	1    10650 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1100 9250 1200
Wire Wire Line
	9250 1200 9400 1200
Wire Wire Line
	10650 1100 10650 1200
Wire Wire Line
	10650 1200 10500 1200
Wire Wire Line
	9950 1500 9950 1650
$Comp
L Device:C C5
U 1 1 5C8BF7A8
P 10500 1400
F 0 "C5" H 10615 1446 50  0000 L CNN
F 1 "10uF" H 10615 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10538 1250 50  0001 C CNN
F 3 "~" H 10500 1400 50  0001 C CNN
	1    10500 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5C8BF895
P 9400 1400
F 0 "C4" H 9515 1446 50  0000 L CNN
F 1 "10uF 25V" H 9515 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9438 1250 50  0001 C CNN
F 3 "~" H 9400 1400 50  0001 C CNN
	1    9400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1650 9400 1550
Wire Wire Line
	9400 1250 9400 1200
Connection ~ 9400 1200
Wire Wire Line
	9400 1200 9650 1200
Wire Wire Line
	10500 1250 10500 1200
Connection ~ 10500 1200
Wire Wire Line
	10500 1200 10250 1200
Wire Wire Line
	10500 1550 10500 1650
Wire Wire Line
	10300 2250 9650 2250
Wire Wire Line
	10300 2350 9650 2350
Wire Wire Line
	10300 2450 9650 2450
Wire Wire Line
	10300 2550 9650 2550
Text Label 9650 2250 0    50   ~ 0
TXD
Text Label 9700 2450 0    50   ~ 0
DTR
Text Label 9650 2650 0    50   ~ 0
GND
$Comp
L Device:Q_NPN_BCE Q2
U 1 1 5C8C1F56
P 9650 3450
F 0 "Q2" H 9840 3496 50  0000 L CNN
F 1 "Q_NPN_BCE" H 9840 3405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9850 3550 50  0001 C CNN
F 3 "~" H 9650 3450 50  0001 C CNN
	1    9650 3450
	-1   0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BCE Q3
U 1 1 5C8C2189
P 9650 4200
F 0 "Q3" H 9840 4154 50  0000 L CNN
F 1 "Q_NPN_BCE" H 9840 4245 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9850 4300 50  0001 C CNN
F 3 "~" H 9650 4200 50  0001 C CNN
	1    9650 4200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R10
U 1 1 5C8C2340
P 10250 3450
F 0 "R10" V 10043 3450 50  0000 C CNN
F 1 "12k" V 10134 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10180 3450 50  0001 C CNN
F 3 "~" H 10250 3450 50  0001 C CNN
	1    10250 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 5C8C23CC
P 10250 4200
F 0 "R11" V 10043 4200 50  0000 C CNN
F 1 "12k" V 10134 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10180 4200 50  0001 C CNN
F 3 "~" H 10250 4200 50  0001 C CNN
	1    10250 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	9850 3450 10100 3450
Wire Wire Line
	9850 4200 10100 4200
Wire Wire Line
	9550 3250 9550 3150
Wire Wire Line
	9550 3150 9250 3150
Wire Wire Line
	9550 4400 9550 4500
Wire Wire Line
	9550 4500 9300 4500
Wire Wire Line
	10400 4200 10550 4200
Wire Wire Line
	10400 3450 10550 3450
Wire Wire Line
	9550 3650 9550 3750
Wire Wire Line
	9550 3750 10550 4000
Wire Wire Line
	10550 4000 10550 4200
Connection ~ 10550 4200
Wire Wire Line
	10550 4200 10800 4200
Wire Wire Line
	9550 4000 9550 3900
Wire Wire Line
	9550 3900 10550 3750
Wire Wire Line
	10550 3750 10550 3450
Connection ~ 10550 3450
Wire Wire Line
	10550 3450 10800 3450
Text Label 10700 3450 0    50   ~ 0
DTR
Text Label 10700 4200 0    50   ~ 0
RTS
Text Label 9250 3150 0    50   ~ 0
nRST
Text Label 9300 4500 0    50   ~ 0
GPIO0
$Comp
L Device:R R12
U 1 1 5C8C5305
P 10350 5200
F 0 "R12" H 10420 5246 50  0000 L CNN
F 1 "470" H 10420 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10280 5200 50  0001 C CNN
F 3 "~" H 10350 5200 50  0001 C CNN
	1    10350 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5C8C53B6
P 10350 5950
F 0 "#PWR0108" H 10350 5700 50  0001 C CNN
F 1 "GND" H 10355 5777 50  0000 C CNN
F 2 "" H 10350 5950 50  0001 C CNN
F 3 "" H 10350 5950 50  0001 C CNN
	1    10350 5950
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5C8C5461
P 10350 5650
F 0 "SW2" V 10304 5798 50  0000 L CNN
F 1 "KEY_FLASH" V 10395 5798 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 10350 5850 50  0001 C CNN
F 3 "" H 10350 5850 50  0001 C CNN
	1    10350 5650
	0    1    1    0   
$EndComp
Wire Wire Line
	10350 5950 10350 5900
Wire Wire Line
	10350 5450 10350 5400
Wire Wire Line
	10350 5050 10350 4900
Wire Wire Line
	10350 4900 10050 4900
Text Label 10050 4900 0    50   ~ 0
GPIO0
$Comp
L power:+3V3 #PWR0109
U 1 1 5C8C6386
P 8800 4650
F 0 "#PWR0109" H 8800 4500 50  0001 C CNN
F 1 "+3V3" H 8815 4823 50  0000 C CNN
F 2 "" H 8800 4650 50  0001 C CNN
F 3 "" H 8800 4650 50  0001 C CNN
	1    8800 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5C8C63F4
P 8800 4850
F 0 "R8" H 8870 4896 50  0000 L CNN
F 1 "470" H 8870 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8730 4850 50  0001 C CNN
F 3 "~" H 8800 4850 50  0001 C CNN
	1    8800 4850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5C8C6760
P 9000 5800
F 0 "SW1" V 8954 5948 50  0000 L CNN
F 1 "KEY_RST" V 9045 5948 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 9000 6000 50  0001 C CNN
F 3 "" H 9000 6000 50  0001 C CNN
	1    9000 5800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5C8C67B8
P 9000 6100
F 0 "#PWR0110" H 9000 5850 50  0001 C CNN
F 1 "GND" H 9005 5927 50  0000 C CNN
F 2 "" H 9000 6100 50  0001 C CNN
F 3 "" H 9000 6100 50  0001 C CNN
	1    9000 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 4650 8800 4700
Wire Wire Line
	8800 5000 8800 5050
Wire Wire Line
	8800 5600 9000 5600
$Comp
L Device:R R9
U 1 1 5C8C8A49
P 9350 5250
F 0 "R9" H 9420 5296 50  0000 L CNN
F 1 "470" H 9420 5205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9280 5250 50  0001 C CNN
F 3 "~" H 9350 5250 50  0001 C CNN
	1    9350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 5600 9350 5600
Wire Wire Line
	9350 5600 9350 5400
Connection ~ 9000 5600
Wire Wire Line
	9350 5100 9350 5000
Wire Wire Line
	9350 5000 9600 5000
Text Label 9450 5000 0    50   ~ 0
nRST
Wire Wire Line
	8800 5050 8450 5050
Connection ~ 8800 5050
Text Label 8450 5050 0    50   ~ 0
GPIO16
Wire Wire Line
	9000 6100 9000 6050
Wire Wire Line
	3650 3550 3200 3550
Text Label 3200 3550 0    50   ~ 0
ADC
$Comp
L Device:R R1
U 1 1 5C8CCED0
P 7450 5000
F 0 "R1" H 7380 4954 50  0000 R CNN
F 1 "220k (1%)" H 7380 5045 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7380 5000 50  0001 C CNN
F 3 "~" H 7450 5000 50  0001 C CNN
	1    7450 5000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5C8CD12A
P 7450 5600
F 0 "R2" H 7380 5554 50  0000 R CNN
F 1 "100k (1%)" H 7380 5645 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7380 5600 50  0001 C CNN
F 3 "~" H 7450 5600 50  0001 C CNN
	1    7450 5600
	-1   0    0    1   
$EndComp
Wire Wire Line
	7450 4850 7450 4650
Wire Wire Line
	7450 5450 7450 5300
$Comp
L power:GND #PWR0111
U 1 1 5C8CE865
P 7450 6000
F 0 "#PWR0111" H 7450 5750 50  0001 C CNN
F 1 "GND" H 7455 5827 50  0000 C CNN
F 2 "" H 7450 6000 50  0001 C CNN
F 3 "" H 7450 6000 50  0001 C CNN
	1    7450 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 5750 7450 6000
Connection ~ 7450 5300
Wire Wire Line
	7450 5300 7450 5150
Text Label 7050 5300 0    50   ~ 0
ADC
Text Label 7450 4750 1    50   ~ 0
ADC_EX
$Comp
L power:+3V3 #PWR0112
U 1 1 5C8D09D8
P 7150 1050
F 0 "#PWR0112" H 7150 900 50  0001 C CNN
F 1 "+3V3" H 7165 1223 50  0000 C CNN
F 2 "" H 7150 1050 50  0001 C CNN
F 3 "" H 7150 1050 50  0001 C CNN
	1    7150 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5C8D0A60
P 7750 1200
F 0 "R3" V 7543 1200 50  0000 C CNN
F 1 "12k" V 7634 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7680 1200 50  0001 C CNN
F 3 "~" H 7750 1200 50  0001 C CNN
	1    7750 1200
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5C8D0ADD
P 7750 1400
F 0 "R4" V 7543 1400 50  0000 C CNN
F 1 "12k" V 7634 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7680 1400 50  0001 C CNN
F 3 "~" H 7750 1400 50  0001 C CNN
	1    7750 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5C8D0B17
P 7750 1600
F 0 "R5" V 7543 1600 50  0000 C CNN
F 1 "12k" V 7634 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7680 1600 50  0001 C CNN
F 3 "~" H 7750 1600 50  0001 C CNN
	1    7750 1600
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5C8D0B53
P 7750 1850
F 0 "R6" V 7543 1850 50  0000 C CNN
F 1 "12k" V 7634 1850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7680 1850 50  0001 C CNN
F 3 "~" H 7750 1850 50  0001 C CNN
	1    7750 1850
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5C8D0B95
P 7750 2100
F 0 "R7" V 7543 2100 50  0000 C CNN
F 1 "12k" V 7634 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7680 2100 50  0001 C CNN
F 3 "~" H 7750 2100 50  0001 C CNN
	1    7750 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5C8D0BED
P 7150 2150
F 0 "#PWR0113" H 7150 1900 50  0001 C CNN
F 1 "GND" H 7155 1977 50  0000 C CNN
F 2 "" H 7150 2150 50  0001 C CNN
F 3 "" H 7150 2150 50  0001 C CNN
	1    7150 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5C8D0C24
P 8550 2150
F 0 "#PWR0114" H 8550 1900 50  0001 C CNN
F 1 "GND" H 8555 1977 50  0000 C CNN
F 2 "" H 8550 2150 50  0001 C CNN
F 3 "" H 8550 2150 50  0001 C CNN
	1    8550 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1050 7150 1200
Wire Wire Line
	7150 1200 7600 1200
Wire Wire Line
	7150 1200 7150 1400
Wire Wire Line
	7150 1850 7600 1850
Connection ~ 7150 1200
Wire Wire Line
	7600 1600 7150 1600
Connection ~ 7150 1600
Wire Wire Line
	7150 1600 7150 1850
Wire Wire Line
	7600 1400 7150 1400
Connection ~ 7150 1400
Wire Wire Line
	7150 1400 7150 1600
$Comp
L Device:C C3
U 1 1 5C8D5CED
P 8400 1850
F 0 "C3" V 8148 1850 50  0000 C CNN
F 1 "100n" V 8239 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8438 1700 50  0001 C CNN
F 3 "~" H 8400 1850 50  0001 C CNN
	1    8400 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	7900 1850 8250 1850
Wire Wire Line
	8550 1850 8550 2150
Wire Wire Line
	7150 2100 7150 2150
Wire Wire Line
	7150 2100 7600 2100
Wire Wire Line
	7900 2100 8250 2100
Wire Wire Line
	7900 1600 8200 1600
Wire Wire Line
	7900 1400 8200 1400
Wire Wire Line
	7900 1200 8200 1200
Text Label 7950 1200 0    50   ~ 0
GPIO0
Text Label 7950 1400 0    50   ~ 0
GPIO2
Text Label 8000 1600 0    50   ~ 0
EN
Text Label 8000 1850 0    50   ~ 0
nRST
Text Label 8000 2100 0    50   ~ 0
GPIO15
$Comp
L power:+3V3 #PWR0115
U 1 1 5C8E6375
P 7950 3000
F 0 "#PWR0115" H 7950 2850 50  0001 C CNN
F 1 "+3V3" H 7965 3173 50  0000 C CNN
F 2 "" H 7950 3000 50  0001 C CNN
F 3 "" H 7950 3000 50  0001 C CNN
	1    7950 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C2
U 1 1 5C8E6444
P 7950 3350
F 0 "C2" H 8065 3396 50  0000 L CNN
F 1 "100uF" H 8065 3305 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D_Pad2.25x2.55mm_HandSolder" H 7950 3350 50  0001 C CNN
F 3 "https://cdn.sos.sk/productdata/4e/42/7346cb17/tajd107k016rnj.pdf" H 7950 3350 50  0001 C CNN
	1    7950 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5C8E64A2
P 7950 3750
F 0 "#PWR0116" H 7950 3500 50  0001 C CNN
F 1 "GND" H 7955 3577 50  0000 C CNN
F 2 "" H 7950 3750 50  0001 C CNN
F 3 "" H 7950 3750 50  0001 C CNN
	1    7950 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 3000 7950 3200
Wire Wire Line
	7950 3500 7950 3650
Wire Wire Line
	3650 3350 3200 3350
Wire Wire Line
	3650 3150 3200 3150
Wire Wire Line
	4850 3150 5500 3150
Wire Wire Line
	4850 3250 5400 3250
Wire Wire Line
	4850 3350 5500 3350
Wire Wire Line
	4850 3450 5400 3450
Wire Wire Line
	4850 3550 5500 3550
Wire Wire Line
	4850 3650 5500 3650
Wire Wire Line
	4850 3750 5400 3750
Wire Wire Line
	4850 3850 5400 3850
Wire Wire Line
	4850 3950 5400 3950
Wire Wire Line
	4850 4050 5500 4050
Wire Wire Line
	4850 4150 5500 4150
Text Label 5200 3150 0    50   ~ 0
GPIO0
Text Label 5200 3250 0    50   ~ 0
TXD
Text Label 5200 3350 0    50   ~ 0
GPIO2
Text Label 5200 3450 0    50   ~ 0
RXD
Text Label 5150 3750 0    50   ~ 0
GPIO12
Text Label 5150 3850 0    50   ~ 0
GPIO13
Text Label 5150 3950 0    50   ~ 0
GPIO14
Text Label 5150 4050 0    50   ~ 0
GPIO15
Text Label 5150 4150 0    50   ~ 0
GPIO16
Text Label 3200 3350 0    50   ~ 0
EN
Text Label 3200 3150 0    50   ~ 0
nRST
$Comp
L RF_Module:ESP-07 U1
U 1 1 5C8E76C7
P 4250 3750
F 0 "U1" H 4250 4728 50  0000 C CNN
F 1 "ESP-07" H 4250 4637 50  0000 C CNN
F 2 "RF_Module:ESP-07_1" H 4250 3750 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 3900 3850 50  0001 C CNN
	1    4250 3750
	1    0    0    -1  
$EndComp
$Comp
L SHT21:SHT21 U2
U 1 1 5C8EED78
P 4300 6300
F 0 "U2" H 4300 6667 50  0000 C CNN
F 1 "SHT21" H 4300 6576 50  0000 C CNN
F 2 "SHT21_FOOTPRINT:nove" H 4300 6300 50  0001 L BNN
F 3 "DFN-6 Sensirion" H 4300 6300 50  0001 L BNN
F 4 "None" H 4300 6300 50  0001 L BNN "Field4"
F 5 "SHT21" H 4300 6300 50  0001 L BNN "Field5"
F 6 "Unavailable" H 4300 6300 50  0001 L BNN "Field6"
F 7 "Sensirion AG" H 4300 6300 50  0001 L BNN "Field7"
F 8 "SHT21 Series 3 V -40 to +125 °C Digital Humidity & Temperature Sensor IC - DFN-6" H 4300 6300 50  0001 L BNN "Field8"
	1    4300 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6200 3500 6200
Wire Wire Line
	3800 6400 3500 6400
Wire Wire Line
	4800 6200 5000 6200
Wire Wire Line
	4800 6400 4800 6500
$Comp
L power:+3V3 #PWR0117
U 1 1 5C8FB65D
P 5100 6200
F 0 "#PWR0117" H 5100 6050 50  0001 C CNN
F 1 "+3V3" H 5115 6373 50  0000 C CNN
F 2 "" H 5100 6200 50  0001 C CNN
F 3 "" H 5100 6200 50  0001 C CNN
	1    5100 6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5C8FB730
P 4800 6650
F 0 "#PWR0118" H 4800 6400 50  0001 C CNN
F 1 "GND" H 4805 6477 50  0000 C CNN
F 2 "" H 4800 6650 50  0001 C CNN
F 3 "" H 4800 6650 50  0001 C CNN
	1    4800 6650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5C8FB936
P 5000 6350
F 0 "C1" H 5115 6396 50  0000 L CNN
F 1 "100n/50V" H 5115 6305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5038 6200 50  0001 C CNN
F 3 "~" H 5000 6350 50  0001 C CNN
	1    5000 6350
	1    0    0    -1  
$EndComp
Connection ~ 5000 6200
Wire Wire Line
	5000 6200 5100 6200
Wire Wire Line
	5000 6500 4800 6500
Connection ~ 4800 6500
Wire Wire Line
	4800 6500 4800 6650
Text Label 3500 6200 0    50   ~ 0
GPIO0
Text Label 3500 6400 0    50   ~ 0
GPIO2
NoConn ~ 4800 6300
$Comp
L Device:Q_NMOS_GDS Q1
U 1 1 5C90AF36
P 6200 1550
F 0 "Q1" H 6405 1596 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 6405 1505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6400 1650 50  0001 C CNN
F 3 "~" H 6200 1550 50  0001 C CNN
	1    6200 1550
	1    0    0    -1  
$EndComp
Text Label 5200 3550 0    50   ~ 0
GPIO4
Text Label 5200 3650 0    50   ~ 0
GPIO5
Wire Wire Line
	6000 1550 5550 1550
Text Label 5550 1550 0    50   ~ 0
GPIO15
Wire Wire Line
	6300 1750 6300 2000
$Comp
L power:GND #PWR0119
U 1 1 5C92757B
P 6300 2000
F 0 "#PWR0119" H 6300 1750 50  0001 C CNN
F 1 "GND" H 6305 1827 50  0000 C CNN
F 2 "" H 6300 2000 50  0001 C CNN
F 3 "" H 6300 2000 50  0001 C CNN
	1    6300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1350 6300 1100
Text Notes 5650 3550 2    50   ~ 0
TRIG
Text Notes 5700 3650 2    50   ~ 0
ECHO
Text Notes 5650 3350 2    50   ~ 0
SDA
Text Notes 5650 3150 2    50   ~ 0
SCL
Text Notes 5650 4050 2    50   ~ 0
OUT
Text Notes 5700 4150 2    50   ~ 0
WAKE
Wire Wire Line
	1800 2700 2100 2700
Wire Wire Line
	1800 2800 2100 2800
Wire Wire Line
	1800 2900 2100 2900
Wire Wire Line
	1800 4100 2100 4100
Wire Wire Line
	1800 4000 2250 4000
Wire Wire Line
	1800 3900 2300 3900
$Comp
L power:+5V #PWR02
U 1 1 5C965857
P 2100 4100
F 0 "#PWR02" H 2100 3950 50  0001 C CNN
F 1 "+5V" H 2115 4273 50  0000 C CNN
F 2 "" H 2100 4100 50  0001 C CNN
F 3 "" H 2100 4100 50  0001 C CNN
	1    2100 4100
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR03
U 1 1 5C969A87
P 2250 4000
F 0 "#PWR03" H 2250 3850 50  0001 C CNN
F 1 "+3V3" H 2265 4173 50  0000 C CNN
F 2 "" H 2250 4000 50  0001 C CNN
F 3 "" H 2250 4000 50  0001 C CNN
	1    2250 4000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5C998962
P 2300 3900
F 0 "#PWR04" H 2300 3650 50  0001 C CNN
F 1 "GND" H 2305 3727 50  0000 C CNN
F 2 "" H 2300 3900 50  0001 C CNN
F 3 "" H 2300 3900 50  0001 C CNN
	1    2300 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1800 3800 2100 3800
$Comp
L power:GND #PWR01
U 1 1 5C998B3D
P 2100 3800
F 0 "#PWR01" H 2100 3550 50  0001 C CNN
F 1 "GND" H 2105 3627 50  0000 C CNN
F 2 "" H 2100 3800 50  0001 C CNN
F 3 "" H 2100 3800 50  0001 C CNN
	1    2100 3800
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J3
U 1 1 5C9A5E6C
P 10500 2350
F 0 "J3" H 10580 2342 50  0000 L CNN
F 1 "Conn_01x06" H 10580 2251 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 10500 2350 50  0001 C CNN
F 3 "~" H 10500 2350 50  0001 C CNN
	1    10500 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5C9A9991
P 9650 2150
F 0 "#PWR05" H 9650 2000 50  0001 C CNN
F 1 "+5V" H 9665 2323 50  0000 C CNN
F 2 "" H 9650 2150 50  0001 C CNN
F 3 "" H 9650 2150 50  0001 C CNN
	1    9650 2150
	1    0    0    -1  
$EndComp
Text Label 1850 2900 0    50   ~ 0
GPIO14
Wire Wire Line
	1800 2600 2100 2600
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5C9C043B
P 9650 2650
F 0 "#FLG0102" H 9650 2725 50  0001 C CNN
F 1 "PWR_FLAG" H 9650 2823 50  0000 C CNN
F 2 "" H 9650 2650 50  0001 C CNN
F 3 "~" H 9650 2650 50  0001 C CNN
	1    9650 2650
	-1   0    0    1   
$EndComp
Text Label 4250 4600 0    50   ~ 0
GND
Wire Wire Line
	9650 2650 10300 2650
Wire Wire Line
	10300 2150 9950 2150
Connection ~ 9950 2150
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5C9C02E8
P 9950 2150
F 0 "#FLG0101" H 9950 2225 50  0001 C CNN
F 1 "PWR_FLAG" H 9950 2324 50  0000 C CNN
F 2 "" H 9950 2150 50  0001 C CNN
F 3 "~" H 9950 2150 50  0001 C CNN
	1    9950 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D2
U 1 1 5C9C3E19
P 3950 1150
F 0 "D2" H 3950 934 50  0000 C CNN
F 1 "D_Schottky" H 3950 1025 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3950 1150 50  0001 C CNN
F 3 "~" H 3950 1150 50  0001 C CNN
	1    3950 1150
	-1   0    0    1   
$EndComp
$Comp
L power:VDD #PWR06
U 1 1 5C9C3FB8
P 3450 1050
F 0 "#PWR06" H 3450 900 50  0001 C CNN
F 1 "VDD" H 3467 1223 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.1mm_L8.5mm_W2.5mm_FlatFork" H 3450 1050 50  0001 C CNN
F 3 "" H 3450 1050 50  0001 C CNN
	1    3450 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5C9C4014
P 4400 1050
F 0 "#PWR07" H 4400 900 50  0001 C CNN
F 1 "+5V" H 4415 1223 50  0000 C CNN
F 2 "" H 4400 1050 50  0001 C CNN
F 3 "" H 4400 1050 50  0001 C CNN
	1    4400 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 1050 3450 1150
Wire Wire Line
	3450 1150 3600 1150
Wire Wire Line
	9650 2150 9950 2150
Wire Wire Line
	4100 1150 4400 1150
Wire Wire Line
	4400 1150 4400 1050
Text Label 6300 1100 0    50   ~ 0
MOS_GND
Wire Wire Line
	1800 3000 2100 3000
Text Label 1900 3700 0    50   ~ 0
GPIO2
Text Label 1900 2600 0    50   ~ 0
GPIO0
Text Label 1900 3500 0    50   ~ 0
GPIO5
Text Label 1900 3600 0    50   ~ 0
GPIO4
Text Label 1850 2700 0    50   ~ 0
GPIO13
Text Label 1850 2800 0    50   ~ 0
GPIO12
Text Label 2100 3000 2    50   ~ 0
ADC_EX
Text Label 1950 4450 0    50   ~ 0
MOS_GND
Wire Wire Line
	1800 4200 1950 4200
Wire Wire Line
	1950 4200 1950 4550
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 5C9FB0B7
P 1600 3900
F 0 "J2" H 1520 3275 50  0000 C CNN
F 1 "Conn_01x08" H 1520 3366 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 1600 3900 50  0001 C CNN
F 3 "~" H 1600 3900 50  0001 C CNN
	1    1600 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 3600 2150 3600
Wire Wire Line
	1800 3700 2150 3700
Wire Wire Line
	1800 3500 2150 3500
Text Label 9650 2350 0    50   ~ 0
RXD
Text Label 9700 2550 0    50   ~ 0
RTS
Wire Wire Line
	8800 5050 8800 5600
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5CA15D7A
P 3600 1150
F 0 "#FLG0103" H 3600 1225 50  0001 C CNN
F 1 "PWR_FLAG" H 3600 1324 50  0000 C CNN
F 2 "" H 3600 1150 50  0001 C CNN
F 3 "~" H 3600 1150 50  0001 C CNN
	1    3600 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1150 3800 1150
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5C916D28
P 3250 1150
F 0 "J4" H 3356 1328 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3050 1200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3250 1150 50  0001 C CNN
F 3 "~" H 3250 1150 50  0001 C CNN
	1    3250 1150
	1    0    0    -1  
$EndComp
Connection ~ 3450 1150
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5C917306
P 1600 2800
F 0 "J1" H 1520 2375 50  0000 C CNN
F 1 "Conn_01x05" H 1520 2466 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 1600 2800 50  0001 C CNN
F 3 "~" H 1600 2800 50  0001 C CNN
	1    1600 2800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 5C917CFB
P 7750 3650
F 0 "J5" H 7856 3828 50  0000 C CNN
F 1 "Conn_01x01_Male" H 7500 3700 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 7750 3650 50  0001 C CNN
F 3 "~" H 7750 3650 50  0001 C CNN
	1    7750 3650
	1    0    0    -1  
$EndComp
Connection ~ 7950 3650
Wire Wire Line
	7950 3650 7950 3750
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 5C918852
P 3450 1350
F 0 "J6" V 3603 1263 50  0000 R CNN
F 1 "Conn_01x01_Male" V 3512 1263 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_2.0x2.0mm" H 3450 1350 50  0001 C CNN
F 3 "~" H 3450 1350 50  0001 C CNN
	1    3450 1350
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J7
U 1 1 5C918A96
P 8150 3650
F 0 "J7" H 8123 3580 50  0000 R CNN
F 1 "Conn_01x01_Male" H 8123 3671 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_2.0x2.0mm" H 8150 3650 50  0001 C CNN
F 3 "~" H 8150 3650 50  0001 C CNN
	1    8150 3650
	-1   0    0    1   
$EndComp
Connection ~ 3600 1150
Wire Wire Line
	7050 5300 7450 5300
$Comp
L Device:C C7
U 1 1 5C9BD771
P 10000 5650
F 0 "C7" H 10115 5696 50  0000 L CNN
F 1 "100n/50V" H 10115 5605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 10038 5500 50  0001 C CNN
F 3 "~" H 10000 5650 50  0001 C CNN
	1    10000 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 5400 10000 5400
Wire Wire Line
	10000 5400 10000 5500
Connection ~ 10350 5400
Wire Wire Line
	10350 5400 10350 5350
Wire Wire Line
	10350 5900 10000 5900
Wire Wire Line
	10000 5900 10000 5800
Connection ~ 10350 5900
Wire Wire Line
	10350 5900 10350 5850
$Comp
L Device:C C6
U 1 1 5C9C6BB8
P 8650 5900
F 0 "C6" H 8765 5946 50  0000 L CNN
F 1 "100n/50V" H 8765 5855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8688 5750 50  0001 C CNN
F 3 "~" H 8650 5900 50  0001 C CNN
	1    8650 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 5750 8650 5650
Wire Wire Line
	8650 5650 9000 5650
Wire Wire Line
	9000 5650 9000 5600
Wire Wire Line
	8650 6050 9000 6050
Connection ~ 9000 6050
Wire Wire Line
	9000 6050 9000 6000
$EndSCHEMATC
