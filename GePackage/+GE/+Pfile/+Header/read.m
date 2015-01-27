%% READ
%
% This function will read a PFiles header information according to the GE
% format defined by the RDBM revision of the file. Using this function
% requires that the proper parsing files have been generated (use  to
% generate files for a specific RBDM revision).

% Note, RBDM revision is not the same as GE revision.
%
% Usage: pfile = GE.Pfile.Header.read([pfile_name], [revision])
%
% Author: Scott Haile Robertson
% Website: www.ScottHaileRobertson.com
%
function pfile = read(varargin)

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
if(~exist(pfile_name,'file'))
    error(['Pfile [' pfile_name '] does not exist!']);
end

% Look up revision if not provided
if(nargin >= 2)
    revision = varargin{2};
else
    revision = GE.Pfile.Header.revision(pfile_name);
end

% Create empty Pfile
pfile = GE.Pfile.Pfile();

% Add the main header
main_header_cmd = ['pfile.rdb = GE.Pfile.Header.RDB' num2str(revision) ...
    '.rdb_' num2str(revision) '(pfile_name,0);'];
eval(main_header_cmd);

% Add the exam header
main_exam_cmd = ['pfile.exam = GE.Pfile.Header.RDB' num2str(revision) ...
    '.exam_' num2str(revision) '(pfile_name,0);'];
eval(main_exam_cmd);

% Add the series header
main_series_cmd = ['pfile.series = GE.Pfile.Header.RDB' num2str(revision) ...
    '.series_' num2str(revision) '(pfile_name,0);'];
eval(main_series_cmd);

% Add the image header
main_image_cmd = ['pfile.image = GE.Pfile.Header.RDB' num2str(revision) ...
    '.image_' num2str(revision) '(pfile_name,0);'];
eval(main_image_cmd);
