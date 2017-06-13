function DATAFFT()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
close all;clear all;clc
load 'E:\MFC\SpeechRecognition\SpeechRecognition\2013-10-2-data2.mat'
data=double(Data);
flashing=double(Flashing);

% window=hanning(100);%增加汉宁窗对数据进行分段处理
% for t1=1:70
%  data((t1-1)*100+1:t1*100)=data((t1-1)*100+1:t1*100).*window';
% end

[c,l]=wavedec(data,3,'haar');%对数据进行3层小波变换
sigma=wnoisest(c,l,1);
alpha=2;
thr=wbmpen(c,l,sigma,alpha);
keepapp=1;
data=wdencmp('gbl',c,l,'db6',3,thr,'s',keepapp);


noise=ones(1,size(data,2));%定义四个矩阵空间用于分别储存噪声数据与语音数据
signal_1=ones(1,size(data,2));
signal_2=ones(1,size(data,2));
signal_3=ones(1,size(data,2));
signal_4=ones(1,size(data,2));
signal_begin=ones(1,8);
t2=1;
t3=0;
t4=1;
t5=1;
t6=1;
t7=1;
for t1=1:size(data,2)
    if flashing(t1)==0
        if t1<=size(data,2)-1 && flashing(t1+1)==1
            t3=t3+1;
        end
        noise(t2)=data(t1);
        t2=t2+1;
    else
        switch (t3)
            case 1 
                signal_1(1,t4)=data(t1);
                t4=t4+1;
            case 2
                signal_2(1,t5)=data(t1);
                t5=t5+1;
            case 3
                signal_3(1,t6)=data(t1);
                t6=t6+1;
            case 4
                signal_4(1,t7)=data(t1);
                t7=t7+1;
        end
    end
end

signal_1=signal_1(1,1:t4-1);%对语音数据的矩阵大小进行适应性改变
signal_2=signal_2(1,1:t5-1);
signal_3=signal_3(1,1:t6-1);
signal_4=signal_4(1,1:t7-1);
noise=noise(1,1:t2-1);

% subplot(2,3,1);
% plot(noise,'-r');
% title('noise');
% hold on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%进行快速傅里叶变换
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%对噪声数据FFT变换
fs=450;%采样频率
length=size(noise,2);%数据长度
nfft=2^nextpow2(length);
fft_length=nfft/2+1;
result_noise=fft(noise,nfft)/length;
f=fs/2*linspace(0,1,fft_length);
subplot(2,3,1);
plot(f,2*abs(result_noise(1:fft_length)),'-r');
title('noise-fft');
hold on;
%对声音数据一进行FFT变换
length=size(signal_1,2);
nfft=2^nextpow2(length);
fft_length=nfft/2+1;
result_signal_1=fft(signal_1,nfft)/length;
f=fs/2*linspace(0,1,fft_length);
subplot(2,3,2);
plot(f,2*abs(result_signal_1(1:fft_length)),'-g');
title('signal-data-1');
%对声音数据二进行FFT变换
length=size(signal_2,2);
nfft=2^nextpow2(length);
fft_length=nfft/2+1;
result_signal_2=fft(signal_2,nfft)/length;
f=fs/2*linspace(0,1,fft_length);
subplot(2,3,3);
plot(f,2*abs(result_signal_2(1:fft_length)),'-g');
title('signal-data-2');
%对声音数据三进行FFT变换
length=size(signal_3,2);
nfft=2^nextpow2(length);
fft_length=nfft/2+1;
result_signal_3=fft(signal_3,nfft)/length;
f=fs/2*linspace(0,1,fft_length);
subplot(2,3,4);
plot(f,2*abs(result_signal_3(1:fft_length)),'-g');
title('signal-data-3');
%对声音数据四进行FFT变换
length=size(signal_4,2);
nfft=2^nextpow2(length);
fft_length=nfft/2+1;
result_signal_4=fft(signal_4,nfft)/length;
f=fs/2*linspace(0,1,fft_length);
subplot(2,3,5);
plot(f,2*abs(result_signal_4(1:fft_length)),'-g');
title('signal-data-3');
%显示原始数据以及打标数据
t3=1;
for t1=1:size(data,2)-1;
    if (flashing(t1)==0 && flashing(t1+1)==1) || (flashing(t1)==1 &&flashing(t1+1)==0)
        signal_begin(1,t3)=t1;
        t3=t3+1;
    end
end
subplot(2,3,6);
plot(data);
hold on;
plot(signal_begin(1,1):signal_begin(1,2),data(1,signal_begin(1,1):signal_begin(1,2)),'y');hold on;
plot(signal_begin(1,3):signal_begin(1,4),data(1,signal_begin(1,3):signal_begin(1,4)),'y');hold on;
plot(signal_begin(1,5):signal_begin(1,6),data(1,signal_begin(1,5):signal_begin(1,6)),'y');hold on;
plot(signal_begin(1,7):signal_begin(1,8),data(1,signal_begin(1,7):signal_begin(1,8)),'y');hold on;
hold on;
plot(flashing,'r');
title('data and flashing');
end

