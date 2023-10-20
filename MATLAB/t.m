g = 9.81;
B = -0.0065
R = 287.05;
Ts = 288.15;
ps = 1.01325e+5;
rhos = psl / (R * Ts)
as = sqrt(1.40 * ps / rhos)
z = linspace(0,10000,100);
Tz = Ts + B.*Tz;
pz = ps.*((1 + B.*z./Ts).^(-g/(R*B)));
rhoz = pz./(R.*Tz);
muz = 1.458e-6.* sqrt(Tz)./(1.0+0+110.40./Tz);
a = sqrt(1.40.*pz./rhoz);
Tz = Tz - 273.15;

figure 
hold on
subplot(3,1,1);
plot(rhoz,z);
xlabel('Density, kgm^-3');
ylabel('Altitude, m');

subplot(3,1,2);
plot(Tz,z);
xlabel('Temperature, C');
ylabel('Altitude, m');

subplot(3,1,3);
plot(pz,z);
xlabel('Pressure,Pa');
ylabel('Altitude, m');