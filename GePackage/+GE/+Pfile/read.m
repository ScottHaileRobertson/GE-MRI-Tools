%% READ
% 
% This function reads a GE pfile and returns a Pfile object containing the 
% header info as well as the data in the scan file.
%
% Note #1: This function handles extended dynamic range
% Note #2: This function does not remove baseline views.
%
% Usage: pfile = GE.Pfile.read([pfile_name], [revision])
%
% Author: Scott Haile Robertson
% Website: www.ScottHaileRobertson.com
%
function pfile = read(varargin)

%% Load inputs if they are given, otherwise povide defaults
% Check if pfile filename is provided - if not, ask for one
pfile_name = [];
if(nargin >= 1)
    pfile_name = varargin{1};
    
    
end
if(isempty(pfile_name))
        [file, path] = uigetfile('*.*', 'Select Pfile');
        pfile_name = strcat(path, file);
end

% Check for revision
revision = [];
if(nargin > 2)
    revision = varargin{2};
end

%% Read the P-file Header
if(isempty(revision))
	% Try to figure out revision automatically
	pfile = GE.Pfile.Header.read(pfile_name);
else
    % Read header for specific revision
	pfile = GE.Pfile.Header.read(pfile_name, revision);
end

% Check if extended dynamic range is used
switch(pfile.rdb.rdb_hdr_point_size)
	case 2
		precision = 'int16';
	case 4
		precision = 'int32';
	otherwise
		error('Only 2 and 4 are accepted as extended dynamic range options.');
end

% Read data from pfile
fid = fopen(pfile.rdb.base_p_file, 'r', 'ieee-le');
fseek(fid, pfile.rdb.rdb_hdr_off_data, 'bof');
pfile.data = fread(fid,inf,precision); % would be nice to make this single precision, but MATLAB requires double for using sparse matrices... sigh
fclose(fid);

% Make data complex (real and imaginary parts alternate in pfile)
revision = floor(pfile.rdb.rdb_hdr_rdbm_rev);
if(revision == 15)
    pfile.data = complex(pfile.data(1:2:end),-pfile.data(2:2:end));
elseif(revision == 11)
    pfile.data = complex(pfile.data(1:2:end),pfile.data(2:2:end));
else
    error('Only GE rev 11 and 15 are currently supported');
end
% Reshape into [npts x frames]
npts = pfile.rdb.rdb_hdr_frame_size;%view points
nframes  = length(pfile.data(:))/npts;
pfile.data = reshape(pfile.data,[npts nframes]);% Reshape into matrix [npts x nframes]

end % function
