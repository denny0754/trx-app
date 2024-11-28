/* Project Headers */
#include <trx/core/ui/Layer.hpp>

namespace trx
{

    Layer::Layer(const std::string& layer_name)
    {
        m_layerName = layer_name;
    }

    const std::string& Layer::GetLayerName() const
    {
        return m_layerName;
    }

}