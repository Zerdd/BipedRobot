data=load('Feedback_Right.txt');
X=data(:,6);




Y0=data(:,1);
figure(1);
plot(X,Y0);
grid on;
set(gca,'XLim',[0  length(data(:,1))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('rightLegHip1')


Y1=data(:,2);
figure(2);
plot(X,Y1);
grid on;
set(gca,'XLim',[0  length(data(:,2))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('rightLegHip2')


Y2=data(:,3);
figure(3);
plot(X,Y2);
grid on;
set(gca,'XLim',[0  length(data(:,3))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('rightLegKnee')


Y3=data(:,4);
figure(4);
plot(X,Y3);
grid on;
set(gca,'XLim',[0  length(data(:,4))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('rightLegAnkle1')



Y4=data(:,5);
figure(5);
plot(X,Y4);
grid on;
set(gca,'XLim',[0  length(data(:,5))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('rightLegAnkle2')





data=load('Feedback_Left.txt');
X=data(:,6);




Y5=data(:,1);
figure(6);
plot(X,Y5);
grid on;
set(gca,'XLim',[0  length(data(:,1))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('LeftLegHip1')


Y6=data(:,2);
figure(7);
plot(X,Y6);
grid on;
set(gca,'XLim',[0  length(data(:,2))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('LeftLegHip2')


Y7=data(:,3);
figure(8);
plot(X,Y7);
grid on;
set(gca,'XLim',[0  length(data(:,3))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('LeftLegKnee')


Y8=data(:,4);
figure(9);
plot(X,Y8);
grid on;
set(gca,'XLim',[0  length(data(:,4))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('LeftLegAnkle1')



Y9=data(:,5);
figure(10);
plot(X,Y9);
grid on;
set(gca,'XLim',[0  length(data(:,5))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('LeftLegAnkle2')