%% REVISION
%
% This function reads a GE pfile and returns the software revision
% of the scan file.
%
% Usage: [revision] = GE.Pfile.Header.revision([pfile_name])
%
% Author: Scott Haile Robertson
% Website: www.ScottHaileRobertson.com
%
function [revision] = revision(varargin)

% Check if pfile filename is provided - if not, ask for one
pfile_name = [];
if(nargin >= 1)
    pfile_name = varargin{1};
end
if(isempty(pfile_name))
    [file, path] = uigetfile('*.*', 'Select Pfile');
    pfile_name = strcat(path, file);
end

% Check that pfile exists
if(~exist(pfile_name))
    error(['Pfile [' pfile_name '] does not exist!']);
end

% Open the PFile
fid=fopen(pfile_name,'r','ieee-le');         %Little-Endian format
if (fid == -1)
    error(sprintf('Could not open %s file.',pfile_name));
end

% start at correct offset
fseek(fid,0,'bof');

% Get GE revision
revision = floor(fread(fid,1,'float32','ieee-le'));

% Close file
fclose(fid);