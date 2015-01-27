%% DEMO_WRITECSVHEADER  
%
%   A demonstration of how to write a pfile header to CSV format
%
%   Author: Scott Haile Robertson
%   Website: www.ScottHaileRobertson.com
% 

% Ask nicely for pfile
pfile = GE.Pfile.Header.read();

% Ask nicely for location to put header data
[write_file, write_path] = uiputfile('*.*', 'Where do you want to save header data?');
if(isempty(regexp(write_file,'.*.csv$')))
    write_file = [write_file '.csv'];
end;
csv_filename = [write_path filesep() write_file];

% Write CSV file, and display it
GE.Pfile.Header.Write.csv(csv_filename, pfile, 1);
