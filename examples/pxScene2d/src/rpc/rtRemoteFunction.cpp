#include "rtRemoteFunction.h"
#include "rtRpcClient.h"

rtRemoteFunction::rtRemoteFunction(std::string const& id, std::string const& name, std::shared_ptr<rtRpcClient> const& client)
  : m_ref_count(0)
  , m_id(id)
  , m_name(name)
  , m_rpc_client(client)
{
}

rtRemoteFunction::~rtRemoteFunction()
{
  Release();
}

rtError
rtRemoteFunction::Send(int argc, rtValue const* argv, rtValue* result)
{
  return m_rpc_client->send(m_id, m_name, argc, argv, result);
}

unsigned long
rtRemoteFunction::AddRef()
{
  return rtAtomicInc(&m_ref_count);
}

unsigned long
rtRemoteFunction::Release()
{
  unsigned long n = rtAtomicDec(&m_ref_count);
  if (n == 0)
    delete this;
  return n;
}
