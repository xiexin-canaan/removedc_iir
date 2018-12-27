function [y]=dc_iir_fxp(x, SOS, G, MCFlag, WLen)
x = double(fi(x,1,16,15));%Q(16,15)，输入信号固定按16bit量化
%% init
Len = length(x);
Sec = size(SOS,1);
for iSec=1:Sec
    Num = SOS(iSec,1:3) * G(iSec);
    Den = SOS(iSec,4:6);
    Pow2 = max(ceil(log2(abs([Num,Den]))));
    Num = my_fi(Num/2^Pow2,WLen,'Nearest');
    Den = my_fi(Den/2^Pow2,WLen,'Nearest');
    Reg = zeros(1,3);
    switch MCFlag
        case 'c'
            x = dc_iir_fxp_c(int32(x*2^15),int32(Num*2^(WLen-1)),int32(Den*2^(WLen-1)),int32(Pow2),int32(WLen));
            x = double(x)/2^15;
        case 'matlab'
            for ii=1:Len
                Reg(1) = Num(1) * x(ii) + Reg(2);
                Reg(1) = Reg(1) * 2^Pow2;
                Reg(1) = my_fi(Reg(1),WLen,'Nearest');
                Reg(2) = Num(2) * x(ii) + Reg(3) - Den(2) * Reg(1);
                Reg(2) = my_fi(Reg(2),WLen,'Nearest');
                Reg(3) = Num(3) * x(ii) - Den(3) * Reg(1);
                Reg(3) = my_fi(Reg(3),WLen,'Nearest');
                x(ii) = Reg(1);
            end
            x = my_fi(x,16,'Nearest');
    end
end
y = my_fi(x * G(end),16,'Floor');

function y=my_fi(x,Wl,Mode)
y = double(fi(x,1,Wl,Wl-1,'RoundMode',Mode));