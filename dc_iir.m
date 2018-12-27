function [y]=dc_iir(x, SOS, G)
%% init
Len = length(x);
Sec = size(SOS,1);
for iSec=1:Sec
    Num = SOS(iSec,1:3) * G(iSec);
    Den = SOS(iSec,4:6);
    Reg = zeros(1,3);
    for ii=1:Len
        Reg(1) = Num(1) * x(ii) + Reg(2);
        Reg(2) = Num(2) * x(ii) + Reg(3) - Den(2) * Reg(1);
        Reg(3) = Num(3) * x(ii) - Den(3) * Reg(1);
        x(ii) = Reg(1);
    end
end
y = x * G(end);