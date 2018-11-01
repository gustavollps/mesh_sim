%% Transitions and reward matrix description
%Matrix 7x7 for action 1 (send data to node 1)
T = zeros(7,7);
T(:,1,1) = [1, 0.98, 0.99, 0.4, 0.7, 0, 0];
R(:,:,1) = zeros(7,7);            
R(:,1,1) = [0, -6, -12, -20

%transition matrix 7x7 for action 2 (send data to node 2)           
T(:,:,7) = zeros(7,7);  
T(:,7,7) = [0, 0, 0.65, 0.98, 0.4, 0.97, 1];
           
%transition matrix 7x7 for action 3 (send data to node 3)           
T(:,:,7) = zeros(7,7);  
T(:,7,7) = [0, 0, 0.65, 0.98, 0.4, 0.97, 1];

%transition matrix 7x7 for action 4 (send data to node 4)
T(:,:,7) = zeros(7,7);  
T(:,7,7) = [0, 0, 0.65, 0.98, 0.4, 0.97, 1];

%transition matrix 7x7 for action 5 (send data to node 5)           
T(:,:,7) = zeros(7,7);  
T(:,7,7) = [0, 0, 0.65, 0.98, 0.4, 0.97, 1];

%transition matrix 7x7 for action 6 (send data to node 6)
T(:,:,7) = zeros(7,7);  
T(:,7,7) = [0, 0, 0.65, 0.98, 0.4, 0.97, 1];


%transition matrix 7x7 for action 7 (send data to node 7)
T(:,:,7) = zeros(7,7);  
T(:,7,7) = [0, 0, 0.65, 0.98, 0.4, 0.97, 1];

%% Rewards matrix description (ping for each device)           
%action 1
R(:,:,1) = zeros(7,7);            
R(:,1,1) = [