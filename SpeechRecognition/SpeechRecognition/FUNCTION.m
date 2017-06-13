% close all;clear all;clc
% load 'VoiceData.mat'
% data=double(DATA);
% temp=data(1:1000);
% plot(temp);
% grid on;
% hold on;
% title('…˘“Ù«˙œﬂ');
% %xlable('TIME');
% % ylable('POWER');
%  nfft=256;
% fs=1000;
% window=hanning(256);
% noverlap=128;
% [pyy,f]=PSD(temp,nfft,fs,window,noverlap);
% figure,plot(f,pyy);
function FUNCTION()
close all;clear all;clc
load 'TestData.mat'
data=double(DATA(1:3000));
flashing=double(Flashing(1:3000));
plot(data);
hold on;
plot(flashing);
hold on;
end