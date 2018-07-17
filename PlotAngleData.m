data=load('Feedback_Right.txt');
X=data(:,11);




Y0=data(:,2);
figure(1);
plot(X,Y0);
grid on;
set(gca,'XLim',[0  length(data(:,1))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle0')


Y1=data(:,4);
figure(2);
plot(X,Y1);
grid on;
set(gca,'XLim',[0  length(data(:,2))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle1')


Y2=data(:,6);
figure(3);
plot(X,Y2);
grid on;
set(gca,'XLim',[0  length(data(:,3))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle2')


Y3=data(:,8);
figure(4);
plot(X,Y3);
grid on;
set(gca,'XLim',[0  length(data(:,4))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle3')



Y4=data(:,10);
figure(5);
plot(X,Y4);
grid on;
set(gca,'XLim',[0  length(data(:,5))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle4')





data=load('Feedback_Left.txt');
X=data(:,11);




Y5=data(:,2);
figure(6);
plot(X,Y5);
grid on;
set(gca,'XLim',[0  length(data(:,1))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle5')


Y6=data(:,4);
figure(7);
plot(X,Y6);
grid on;
set(gca,'XLim',[0  length(data(:,2))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle6')


Y7=data(:,6);
figure(8);
plot(X,Y7);
grid on;
set(gca,'XLim',[0  length(data(:,3))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle7')


Y8=data(:,8);
figure(9);
plot(X,Y8);
grid on;
set(gca,'XLim',[0  length(data(:,4))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle8')



Y9=data(:,10);
figure(10);
plot(X,Y9);
grid on;
set(gca,'XLim',[0  length(data(:,5))]);
%set(gca,'YLim',[-90 90]);
xlabel('time')   
ylabel('CurrentAngle9')