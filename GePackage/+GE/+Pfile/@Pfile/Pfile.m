%% PFILE
%
%   An class that knows how to read and understand GE's PFile format
%
% Author: Scott Haile Robertson
% Website: www.ScottHaileRobertson.com
%
classdef Pfile
    properties
        rdb;
        image;
        series;
        exam;
        data;
    end
    
    methods
        % Constructor 
        % NOTE - you can have a blank pfile object - if you wanted to read
        % a Pfile, use GE.Pfile.read()
        function obj = Pfile(varargin)
            
            % If pfile filename is given, use it
            if(nargin >= 1)
                pfile_name = varargin{1};
                
                % Check if pfile filename exists
                if(isempty(pfile_name))
                    [file, path] = uigetfile('*.*', 'Select Pfile');
                    pfile_name = strcat(path, file);
                end
                
                % Read given pfile
                obj = GE.Pfile.Header.read(pfile_name);
            end
        end
    end
end