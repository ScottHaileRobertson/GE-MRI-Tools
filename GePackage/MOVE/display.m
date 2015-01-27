%% DISPLAY
%
% This function displays information from a GE pfile 
%
% Usage: display(pfile, {rdb,exam,series,image},[filter])
%
% Author: Scott Haile Robertson
% Website: www.ScottHaileRobertson.com
%
function display(varargin)

% Parse inputs
if(nargin < 1)
    [file, path] = uigetfile('*.*', 'Select Pfile');
    pfile_name = strcat(path, file);
end

% Read pfile header
GE.Pfile.Header.read(pfile_name);




fprintf('Displaying header info for %s...\n',header.rdb.base_p_file);
fprintf('\tName = %s\n',header.exam.patid');
fprintf('\tWeight = %0.0f lbs (%0.0f kg)\n',round(header.exam.patweight/453.592),round(header.exam.patweight/1000));

fprintf('\tTE=%f usec\n',header.image.te);
fprintf('\tTR=%f usec\n',header.image.tr);
fprintf('\topflip=%0.1f degrees\n',header.rdb.rdb_hdr_user0);
fprintf('\tlopflip=%0.1f degrees\n',header.rdb.rdb_hdr_user36);
fprintf('\tBW=%f kHz\n',header.rdb.rdb_hdr_user12);
fprintf('\tFOV=%0.0f cm\n',header.rdb.rdb_hdr_fov);
fprintf('\tslice thickness=%0.0f mm\n',header.rdb.rdb_hdr_user20);

fprintf('\tnPts=%0.0f\n',header.rdb.rdb_hdr_frame_size);
fprintf('\tnFrames=%0.0f\n',header.rdb.rdb_hdr_user20);
fprintf('\thardpulse=%0.0f\n',header.rdb.rdb_hdr_user39);
if(~header.rdb.rdb_hdr_user39)
	fprintf('\tnoslice=%0.0f\n',header.rdb.rdb_hdr_user34);
	if(~header.rdb.rdb_hdr_user34)
		fprintf('\trephasertime=%f\n',header.rdb.rdb_hdr_user35);
	end
end
fprintf('\tsinct=%f\n',header.rdb.rdb_hdr_user33);
fprintf('\tdummy=%0.0f\n',header.rdb.rdb_hdr_user37);

fprintf('\tper_nufft=%0.0f\n',header.rdb.rdb_hdr_user32);
fprintf('\tloopfactor=%0.0f\n',header.rdb.rdb_hdr_user10);

fprintf('\tTG=%0.0f\n',header.rdb.rdb_hdr_ps_mps_tg);
fprintf('\tR1=%0.0f/15\n',header.rdb.rdb_hdr_ps_mps_r1);
data_size_bytes = header.rdb.rdb_hdr_point_size;
if(data_size_bytes == 4)
	%	Extended dynamic range is on
	fprintf('\tR2=%0.0f/30 (Extended dynamic range on)\n',header.rdb.rdb_hdr_ps_mps_r2);
else
	fprintf('\tR2=%0.0f/15 (Extended dynamic range off)\n',header.rdb.rdb_hdr_ps_mps_r2);
end
fprintf('\tfrequency=%0.0f\n',header.rdb.rdb_hdr_ps_mps_freq);

% Readout gradients
fprintf('\tReadout Gradients:\n');
fprintf('\t\tInstruction Amplitude = %f\n',header.rdb.rdb_hdr_user27);
fprintf('\t\tGradient Delay = %f usec\n',header.rdb.rdb_hdr_user22);
fprintf('\t\tAscending ramp = %f usec\n',header.rdb.rdb_hdr_user1);
fprintf('\t\tPlateau        = %f usec\n',header.rdb.rdb_hdr_user44);
fprintf('\t\tDecending ramp = %f usec\n',header.rdb.rdb_hdr_user38);
end