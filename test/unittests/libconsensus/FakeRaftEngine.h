#include <libconsensus/raft/RaftEngine.h>

namespace dev
{
namespace test
{
class FakeRaftEngine : public dev::consensus::RaftEngine
{
public:
    FakeRaftEngine(std::shared_ptr<dev::p2p::P2PInterface> _service,
        std::shared_ptr<dev::txpool::TxPoolInterface> _txPool,
        std::shared_ptr<dev::blockchain::BlockChainInterface> _blockChain,
        std::shared_ptr<dev::sync::SyncInterface> _blockSync,
        std::shared_ptr<dev::blockverifier::BlockVerifierInterface> _blockVerifier,
        KeyPair const& _keyPair, unsigned _minElectTime, unsigned _maxElectTime,
        dev::PROTOCOL_ID const& _protocolId, dev::h512s const& _minerList = dev::h512s())
      : RaftEngine(_service, _txPool, _blockChain, _blockSync, _blockVerifier, _keyPair,
            _minElectTime, _maxElectTime, _protocolId, _minerList)
    {}

    /*
    void updateMinerList()
    {
        if (m_highestBlock.number() == m_lastObtainMinerNum)
            return;
        m_lastObtainMinerNum = m_highestBlock.number();
    }
    */
    void updateConsensusNodeList() override {}

    dev::p2p::P2PMessage::Ptr generateVoteReq()
    {
        return dev::consensus::RaftEngine::generateVoteReq();
    }

    dev::p2p::P2PMessage::Ptr generateHeartbeat()
    {
        return dev::consensus::RaftEngine::generateHeartbeat();
    }

    dev::consensus::IDXTYPE getIdx() { return m_idx; }

    dev::consensus::RaftMsgQueue& msgQueue() { return m_msgQueue; }

    void onRecvRaftMessage(dev::p2p::NetworkException _exception,
        dev::p2p::P2PSession::Ptr _session, dev::p2p::P2PMessage::Ptr _message)
    {
        return dev::consensus::RaftEngine::onRecvRaftMessage(_exception, _session, _message);
    }

    ssize_t getIndexByMiner(dev::h512 const& _nodeId)
    {
        return dev::consensus::RaftEngine::getIndexByMiner(_nodeId);
    }

    bool getNodeIdByIndex(h512& _nodeId, const u256& _nodeIdx) const
    {
        return dev::consensus::RaftEngine::getNodeIdByIndex(_nodeId, _nodeIdx);
    }

    void setState(dev::consensus::RaftRole _role) { m_state = _role; }

    void setTerm(size_t _term) { m_term = _term; }

    void setVote(dev::consensus::raft::NodeIndex _vote)
    {
        dev::consensus::RaftEngine::setVote(_vote);
    }

    void setFirstVote(dev::consensus::raft::NodeIndex _firstVote) { m_firstVote = _firstVote; }

    void setLastLeaderTerm(size_t _term) { m_lastLeaderTerm = _term; }

    void setUncommitedBlock(dev::eth::Block const& _block) { m_uncommittedBlock = _block; }

    dev::eth::Block& getUncommitedBlock() { return m_uncommittedBlock; }

    std::shared_ptr<dev::blockchain::BlockChainInterface> getBlockChain() { return m_blockChain; }

    dev::eth::BlockHeader getHighestBlock()
    {
        return dev::consensus::RaftEngine::getHighestBlock();
    }

    dev::consensus::RaftRole getState() const { return dev::consensus::RaftEngine::getState(); }

    bool runAsLeaderImp(std::unordered_map<dev::h512, unsigned>& memberHeartbeatLog)
    {
        return dev::consensus::RaftEngine::runAsLeaderImp(memberHeartbeatLog);
    }

    bool runAsFollowerImp() { return dev::consensus::RaftEngine::runAsFollowerImp(); }

    bool runAsCandidateImp(dev::consensus::VoteState _voteState)
    {
        return dev::consensus::RaftEngine::runAsCandidateImp(_voteState);
    }

    bool checkHeartbeatTimeout() override
    {
        dev::consensus::RaftEngine::checkHeartbeatTimeout();
        return heartbeatTimeout;
    }

    bool checkElectTimeout() override
    {
        dev::consensus::RaftEngine::checkElectTimeout();
        return electTimeout;
    }

    bool handleHeartbeat(
        dev::u256 const& _from, dev::h512 const& _node, dev::consensus::RaftHeartBeat const& _hb)
    {
        return dev::consensus::RaftEngine::handleHeartbeat(_from, _node, _hb);
    }

    bool handleVoteRequest(
        dev::u256 const& _from, dev::h512 const& _node, dev::consensus::RaftVoteReq const& _req)
    {
        return dev::consensus::RaftEngine::handleVoteRequest(_from, _node, _req);
    }

    dev::consensus::HandleVoteResult handleVoteResponse(dev::u256 const& _from,
        dev::h512 const& _node, dev::consensus::RaftVoteResp const& _resp,
        dev::consensus::VoteState& vote)
    {
        return dev::consensus::RaftEngine::handleVoteResponse(_from, _node, _resp, vote);
    }

    void reportBlock(dev::eth::Block const& _block)
    {
        dev::consensus::RaftEngine::reportBlock(_block);
    }

    void workLoop() {}

    bool heartbeatTimeout = false;
    bool electTimeout = false;
};
}  // namespace test
}  // namespace dev