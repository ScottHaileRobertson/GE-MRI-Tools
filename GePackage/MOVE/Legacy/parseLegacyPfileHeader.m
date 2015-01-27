function newHeader = parseLegacyPfileHeader(legacyHeader)
newHeader = legacyHeader;

nPts = header.rdb.rdb_hdr_frame_size; 
bw = header.rdb.rdb_hdr_user12;                 % Receiver bandwidth (kHz)
dwell_time = 1/(2*bw);                                             % Time between each sample
dwell_time = nearestMultipleOf(dwell_time,0.002); % Dwell time must be an integer multible of 2us
header.rdb.rdb_hdr_user44 = (nPts -header.rdb.rdb_hdr_user42)*dwell_time; %plateau time
%%% Note if you are at min TE, uncomment the next line
% header.rdb.rdb_hdr_user44 = 0.5*header.rdb.rdb_hdr_user44;