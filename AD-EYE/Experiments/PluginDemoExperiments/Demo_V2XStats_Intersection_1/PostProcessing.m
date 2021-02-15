load('ideal.mat');
load('warning.mat');

success_rate_lane1 = 100*sum(warning(2,:))/sum(ideal(2,:));
% success_rate_lane2 =100*sum(warning(3,:))/sum(ideal(3,:))
% success_rate_lane3 =100*sum(warning(4,:))/sum(ideal(4,:))