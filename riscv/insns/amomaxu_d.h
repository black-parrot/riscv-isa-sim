//Disable for BP
require(0);
require_extension('A');
require_rv64;
WRITE_RD(MMU.amo_uint64(RS1, [&](uint64_t lhs) { return std::max(lhs, RS2); }));
