function Plot_Com()
%PLOT Summary of this function goes here
%   Detailed explanation goes here

% Compression Cement and Carbon
    % in x
    text_X = fileread('Com_x.txt');
    linesX = splitlines(text_X);

    kX = zeros(501,11);
    %disp(k)

    for i = 2:1:502
        str = split(linesX{i});
        %disp(str)
        linesX{i} = strcat(str{2},32,str{3},32,str{4},32,str{5},32,str{6},32,str{7},32,str{8},32,str{9},32,str{10},32,str{11},32,str{12});
        %disp(lines{i})
        kX(i-1,:) = str2num(linesX{i});
        
    end

    vmsX = transpose(sqrt(0.5*((kX(:,4)/10-kX(:,5)/10)'.^2+(kX(:,5)/10-kX(:,6)/10)'.^2+(kX(:,6)/10-kX(:,4)/10)'.^2)));

    strainX = abs((kX(:,9)-kX(1,9))/kX(1,9));

    [row, col] = find(strainX <= 0.02,1,"last");
    disp('Value Sigma X 1')
    disp(vmsX(row,col))
    [row, col] = find(strainX<=0.035,1,"last");
    disp('Value Sigma X 2')
    disp(vmsX(row,col))

    % in y
    text_Y = fileread('Com_y.txt');
    linesY = splitlines(text_Y);

    kY = zeros(501,11);
    %disp(k)

    for i = 2:1:502
        str = split(linesY{i});
        %disp(str)
        linesY{i} = strcat(str{2},32,str{3},32,str{4},32,str{5},32,str{6},32,str{7},32,str{8},32,str{9},32,str{10},32,str{11},32,str{12});
        %disp(lines{i})
        kY(i-1,:) = str2num(linesY{i});
        
    end

    vmsY = transpose(sqrt(0.5*((kY(:,4)/10-kY(:,5)/10)'.^2+(kY(:,5)/10-kY(:,6)/10)'.^2+(kY(:,6)/10-kY(:,4)/10)'.^2)));

    strainY = abs((kY(:,10)-kY(1,10))/kY(1,10));

    [row, col] = find(strainY <= 0.02,1,"last");
    disp('Value Sigma Y 1')
    disp(vmsY(row,col))
    [row, col] = find(strainY<=0.035,1,"last");
    disp('Value Sigma Y 2')
    disp(vmsY(row,col))

    % in z

    text_Z = fileread('Com_z.txt');
    linesZ = splitlines(text_Z);

    kZ = zeros(501,11);
    %disp(k)

    for i = 2:1:502
        str = split(linesZ{i});
        %disp(str)
        linesZ{i} = strcat(str{2},32,str{3},32,str{4},32,str{5},32,str{6},32,str{7},32,str{8},32,str{9},32,str{10},32,str{11},32,str{12});
        %disp(lines{i})
        kZ(i-1,:) = str2num(linesZ{i});
        
    end

    vmsZ = transpose(sqrt(0.5*((kZ(:,4)/10-kZ(:,5)/10)'.^2+(kZ(:,5)/10-kZ(:,6)/10)'.^2+(kZ(:,6)/10-kZ(:,4)/10)'.^2)));

    strainZ = abs((kZ(:,11)-kZ(1,11))/kZ(1,11));

    [row, col] = find(strainZ <= 0.02,1,"last");
    disp('Value Sigma Z 1')
    disp(vmsZ(row,col))
    [row, col] = find(strainZ<=0.035,1,"last");
    disp('Value Sigma Z 2')
    disp(vmsZ(row,col))


    % Compression Cement only
    % in x
    text_X_C = fileread('Com_x_Co.txt');
    linesX_C = splitlines(text_X_C);

    kX_C = zeros(501,11);
    %disp(k)

    for i = 2:1:502
        str = split(linesX_C{i});
        %disp(str)
        linesX_C{i} = strcat(str{2},32,str{3},32,str{4},32,str{5},32,str{6},32,str{7},32,str{8},32,str{9},32,str{10},32,str{11},32,str{12});
        %disp(lines{i})
        kX_C(i-1,:) = str2num(linesX_C{i});
        
    end

    vmsX_C = transpose(sqrt(0.5*((kX_C(:,4)/10-kX_C(:,5)/10)'.^2+(kX_C(:,5)/10-kX_C(:,6)/10)'.^2+(kX_C(:,6)/10-kX_C(:,4)/10)'.^2)));

    strainX_C = abs((kX_C(:,9)-kX_C(1,9))/kX_C(1,9));

    [row, col] = find(strainX_C <= 0.02,1,"last");
    disp('Value Sigma X C 1')
    disp(vmsX_C(row,col))
    [row, col] = find(strainX_C<=0.035,1,"last");
    disp('Value Sigma X C 2')
    disp(vmsX_C(row,col))

    % in y
    text_YC = fileread('Com_y_Co.txt');
    linesYC = splitlines(text_YC);

    kYC = zeros(501,11);
    %disp(k)

    for i = 2:1:502
        str = split(linesYC{i});
        %disp(str)
        linesYC{i} = strcat(str{2},32,str{3},32,str{4},32,str{5},32,str{6},32,str{7},32,str{8},32,str{9},32,str{10},32,str{11},32,str{12});
        %disp(lines{i})
        kYC(i-1,:) = str2num(linesYC{i});
        
    end

    vmsYC = transpose(sqrt(0.5*((kYC(:,4)/10-kYC(:,5)/10)'.^2+(kYC(:,5)/10-kYC(:,6)/10)'.^2+(kYC(:,6)/10-kYC(:,4)/10)'.^2)));

    strainYC = abs((kYC(:,10)-kYC(1,10))/kYC(1,10));

    [row, col] = find(strainYC <= 0.02,1,"last");
    disp('Value Sigma Y C 1')
    disp(vmsYC(row,col))
    [row, col] = find(strainYC<=0.035,1,"last");
    disp('Value Sigma Y C 2')
    disp(vmsYC(row,col))

    % in z

    text_ZC = fileread('Com_Z_Co.txt');
    linesZ_C = splitlines(text_ZC);

    kZ = zeros(501,11);
    %disp(k)

    for i = 2:1:502
        str = split(linesZ_C{i});
        %disp(str)
        linesZ_C{i} = strcat(str{2},32,str{3},32,str{4},32,str{5},32,str{6},32,str{7},32,str{8},32,str{9},32,str{10},32,str{11},32,str{12});
        %disp(lines{i})
        kZC(i-1,:) = str2num(linesZ_C{i});
        
    end

    vmsZC = transpose(sqrt(0.5*((kZC(:,4)/10-kZC(:,5)/10)'.^2+(kZC(:,5)/10-kZC(:,6)/10)'.^2+(kZC(:,6)/10-kZC(:,4)/10)'.^2)));

    strainZC = abs((kZC(:,11)-kZC(1,11))/kZC(1,11));

    [row, col] = find(strainZC <= 0.02,1,"last");
    disp('Value Sigma Z C 1')
    disp(vmsZC(row,col))
    [row, col] = find(strainZC<=0.035,1,"last");
    disp('Value Sigma Z C 2')
    disp(vmsZC(row,col))


    % Plot 
    figure
    plot(abs(strainX),abs(vmsX))
    hold on
    plot(abs(strainY),abs(vmsY))
    hold on 
%     plot(abs(strainZ),abs(vmsZ))
%     hold on
    plot(abs(strainX_C),abs(vmsX_C))
    hold on
    plot(abs(strainYC),abs(vmsYC))
%     hold on 
%     plot(abs(strainZC),abs(vmsZC))
    xlabel('Strain [A/A]')
    ylabel('Stress [MPa]')
    legend('Loading in x Direction, with fiber','Loading in y Direction, with fiber','Loading in x Direction, without fiber','Loading in y Direction, without fiber');


end

