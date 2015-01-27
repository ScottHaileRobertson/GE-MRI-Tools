% Get current path
rootDistribDir = pwd();

% Add GE package to path
disp('Adding GE package to MATLAB path...');
path(genpath([rootDistribDir filesep() 'GePackage']),path);

