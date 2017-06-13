function SHOWDATA()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
load '2013-10-2-test.mat'
subplot(1,2,1);
plot(Data,'-r');
subplot(1,2,2);
plot(Flashing,'-r');
hold on;
end

